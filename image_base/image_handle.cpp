//
// Created by Will nicht on 28.07.18.
//

#include "image_handle.h"
namespace ip {
    int image_handle::load_image(const std::string& imagePath) {
        this->m_image = imread(imagePath, IMREAD_COLOR);
        namedWindow( "OutputImage", WINDOW_AUTOSIZE );
        if (this->m_image.empty()){
            return ERROR_NO_IMAGE;
        }
        return NO_ERROR;
    }

    void image_handle::set_reductor(int divided) {
        this->m_reduce_div = divided;
        for (int i = 0; i < REDUCE_TABLE_SIZE; ++i)
            this->m_table[i] = (uchar)(m_reduce_div * (i/m_reduce_div));
    }

    void image_handle::reduce(bool show) {
        Mat lookUpTable(1, REDUCE_TABLE_SIZE, CV_8U);
        auto p = lookUpTable.ptr<uchar>(0);
        for( int i = 0; i < REDUCE_TABLE_SIZE; ++i)
            p[i] = this->m_table[i];
        // Buggy?
        if(m_cur.empty())
            LUT(m_image, lookUpTable, m_cur);
        else
            LUT(m_cur, lookUpTable, m_cur);

        // this->m_cur = ScanImageAndReduceC();
        if(show){
            imshow("OutputImage", m_cur);
            waitKey(0);
        } else {
            auto res = imwrite("/tmp/out.jpg", this->m_cur);
        }
    }

    Mat image_handle::ScanImageAndReduceC() {
        auto I = this->m_image.clone();
        CV_Assert(I.depth() == CV_8U);
        int channels = I.channels();
        int nRows = I.rows;
        int nCols = I.cols * channels;
        if (I.isContinuous())
        {
            nCols *= nRows;
            nRows = 1;
        }
        int i,j;
        uchar* p;
        for( i = 0; i < nRows; ++i)
        {
            p = I.ptr<uchar>(i);
            for ( j = 0; j < nCols; ++j)
            {
                p[j] = m_table[p[j]];
            }
        }
        return I;
    }

    void image_handle::sharpen(bool show) {
        Mat kernel = (Mat_<char>(3,3) <<  0, -1,  0,
                -1,  5, -1,
                0, -1,  0);
        if(m_cur.empty()) {
            filter2D(m_image, m_cur, m_image.depth(), kernel );
        } else {
            filter2D(m_cur, m_cur, m_image.depth(), kernel );
        }
        // this->m_cur = ScanImageAndReduceC();
        if(show){
            imshow("OutputImage", m_cur);
            waitKey(0);
        } else {
            auto res = imwrite("/tmp/out.jpg", this->m_cur);
        }
    }

    void image_handle::gamma_correct(double gamma, bool show) {
        Mat lookUpTable(1, REDUCE_TABLE_SIZE, CV_8U);
        uchar* p = lookUpTable.ptr();
        for( int i = 0; i < REDUCE_TABLE_SIZE; ++i)
            p[i] = saturate_cast<uchar>(pow(i / 255.0, gamma) * 255.0);
        if(m_cur.empty())
            LUT(m_image, lookUpTable, m_cur);
        else
            LUT(m_cur, lookUpTable, m_cur);
        if(show){
            imshow("OutputImage", m_cur);
            waitKey(0);
        } else {
            auto res = imwrite("/tmp/out.jpg", this->m_cur);
        }
    }

    Mat image_handle::dft(bool show) {
        Mat padded;                            //expand input image to optimal size
        Mat bw;
        if(m_cur.empty())
            cvtColor(m_image, bw, COLOR_BGR2GRAY);
        else
            cvtColor(m_cur, bw, COLOR_BGR2GRAY);

        // Optimize Size for better Performance (x2, x3, x5 serve beste for fourier transformation)
        int m = getOptimalDFTSize(bw.rows);
        int n = getOptimalDFTSize(bw.cols);
        copyMakeBorder(bw, padded, 0, m - bw.rows, 0, n - bw.cols, BORDER_CONSTANT, Scalar::all(0));
        if(show){
            imshow("OutputImage", padded);
            waitKey(0);
        }
        Mat planes[] = {Mat_<float>(padded), Mat::zeros(padded.size(), CV_32F)};
        Mat complexI;
        merge(planes, 2, complexI);         // Add to the expanded another plane with zeros
        cv::dft(complexI, complexI);            // this way the result may fit in the source matrix

        // compute the magnitude and switch to logarithmic scale
        // => log(1 + sqrt(Re(DFT(I))^2 + Im(DFT(I))^2))
        split(complexI, planes);                   // planes[0] = Re(DFT(I), planes[1] = Im(DFT(I))
        if(show){
            imshow("OutputImage", planes[0]);
            waitKey(0);
        }
        magnitude(planes[0], planes[1], planes[0]);// planes[0] = magnitude
        Mat magI = planes[0];
        magI += Scalar::all(1);                    // switch to logarithmic scale
        log(magI, magI);
        // crop the spectrum, if it has an odd number of rows or columns
        magI = magI(Rect(0, 0, magI.cols & -2, magI.rows & -2));

        if(show){
            imshow("OutputImage", magI);
            waitKey(0);
        }
        // rearrange the quadrants of Fourier image  so that the origin is at the image center
        int cx = magI.cols/2;
        int cy = magI.rows/2;
        Mat q0(magI, Rect(0, 0, cx, cy));   // Top-Left - Create a ROI per quadrant
        Mat q1(magI, Rect(cx, 0, cx, cy));  // Top-Right
        Mat q2(magI, Rect(0, cy, cx, cy));  // Bottom-Left
        Mat q3(magI, Rect(cx, cy, cx, cy)); // Bottom-Right

        Mat tmp;                           // swap quadrants (Top-Left with Bottom-Right)
        q0.copyTo(tmp);
        q3.copyTo(q0);
        tmp.copyTo(q3);
        q1.copyTo(tmp);                    // swap quadrant (Top-Right with Bottom-Left)
        q2.copyTo(q1);
        tmp.copyTo(q2);
        normalize(magI, magI, 0, 1, NORM_MINMAX); // Transform the matrix with float values into a
        // viewable image form (float between values 0 and 1).
        if(show){
            imshow(WINDOW, magI);
            waitKey(0);
        }
        return magI;
    }

    void image_handle::blurBilateral(bool show) {
        Mat blur, target;
        if (m_cur.empty())
            blur = m_cur.clone();
        else
            blur = m_image.clone();

        for ( int i = 1; i < 31; i = i + 2 )
        {

            bilateralFilter ( blur, target, i, i*2, i/2 );
            if(show)
            {
                imshow(WINDOW, target);
                waitKey(10);
            }
        }
        if(show) {
            waitKey(0);
        }

    }

    void image_handle::blurGausian(bool show) {
        Mat blur, target;
        if (m_cur.empty())
            blur = m_cur.clone();
        else
            blur = m_image.clone();

        for ( int i = 1; i < 31; i = i + 2 )
        {
            GaussianBlur( blur, target, Size( i, i ), 0, 0 );
            if(show)
            {
                imshow(WINDOW, target);
                waitKey(10);
            }
        }
        if(show) {
            waitKey(0);
        }
    }

    void image_handle::dilation(int type, bool show) {
        int dilation_size = 5;

        Mat element = getStructuringElement( type,
                                             Size( 2*dilation_size + 1, 2*dilation_size+1 ),
                                             Point( dilation_size, dilation_size ) );

        /// Apply the dilation operation
        if(m_cur.empty())
            dilate( m_image, m_cur, element );
        else
            dilate( m_cur, m_cur, element );
        if(show){
            imshow(WINDOW, m_cur);
            waitKey(0);
        }

    }

    void image_handle::erosion(int type, bool show) {
        int erosion_size = 5;
        //![kernel]
        Mat element = getStructuringElement( type,
                                             Size( 2*erosion_size + 1, 2*erosion_size+1 ),
                                             Point( erosion_size, erosion_size ) );
        //![kernel]

        /// Apply the erosion operation
        if(m_cur.empty())
            erode( m_image, m_cur, element );
        else
            erode( m_cur, m_cur, element );
        if(show){
            imshow(WINDOW, m_cur);
            waitKey(0);
        }
    }
}
