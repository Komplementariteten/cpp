//
// Created by Will nicht on 28.07.18.
//

#ifndef CPP_IMAGE_HANDLE_H
#define CPP_IMAGE_HANDLE_H


#include <string>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

using namespace cv;

namespace ip {
    const int ERROR_NO_IMAGE = -1;
    const int NO_ERROR = 1;
    const int REDUCE_TABLE_SIZE = 256;
    const std::string WINDOW = "OutputImage";
    class image_handle {
    public:
        int load_image(const std::string& imagePath);
        void set_reductor(int divided);
        void sharpen(bool show);
        void reduce(bool show);
        void gamma_correct(double gamma, bool show);
        Mat dft(bool show);
        void blurBilateral(bool show);
        void blurGausian(bool show);
        void dilation(int type, bool show);
        void erosion(int type, bool show);
    private:
        Mat m_image; // Original
        Mat m_cur; //  After some editing
        int m_reduce_div = 0;
        uchar m_table[REDUCE_TABLE_SIZE];
        Mat ScanImageAndReduceC();
    };
}


#endif //CPP_IMAGE_HANDLE_H
