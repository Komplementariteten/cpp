#include <iostream>

#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>

using namespace std;

using namespace cv;
const string WindowName = "IMVIEW";
const string DATA_PATH = "../";
const int PREVIEW_WIDTH = 1280;
const int HALF_WIDTH = PREVIEW_WIDTH / 2;
const int PREVIEW_HEIGHT = 860;

void show_and_wait(const Mat& image)
{
    imshow(WindowName, image);
    waitKey(0);
}

Mat to_rgb(const Mat& image)
{
    Mat output;
    switch (image.type())
    {
        case CV_8UC1:
            cvtColor(image, output, cv::COLOR_GRAY2RGB);
            break;
        default:
            output = image.clone();
            break;
    }
    return output;
}

Mat fit_into_cv(const Mat &image)
{
    Mat output = image.clone();
    auto imgSize = image.size();
    if (imgSize.height > PREVIEW_HEIGHT)
    {
        auto scale = PREVIEW_HEIGHT / static_cast<double>(imgSize.height);
        resize(image, output, Size(), scale, scale, INTER_LINEAR);
        imgSize = output.size();
    }

    if (imgSize.width > HALF_WIDTH)
    {
        auto scale = HALF_WIDTH / static_cast<double>(imgSize.width);
        resize(image, output, Size(), scale, scale, INTER_LINEAR);
    }

    return output;
}

void show2_and_wait(const Mat& image1, const Mat& image2, int type)
{
    Mat imgToShow1 = image1.clone();
    Mat imgToShow2 = image2.clone();
    Mat cavan = Mat(Size(PREVIEW_WIDTH, PREVIEW_HEIGHT),type, Scalar(0, 0, 0)).clone();

    // Scale Image 1
    auto img1Size = image1.size();
    if (img1Size.height > img1Size.width)
    {
        auto scale = PREVIEW_HEIGHT / static_cast<double>(img1Size.height);
        resize(imgToShow1, imgToShow1, Size(), scale, scale, INTER_LINEAR);
        imgToShow1 = fit_into_cv(imgToShow1);
        img1Size = imgToShow1.size();
        imgToShow1.copyTo(cavan(Range(0, img1Size.height), Range(0, img1Size.width)));
    } else {
        auto scale = HALF_WIDTH / static_cast<double>(img1Size.width);
        resize(imgToShow1, imgToShow1, Size(), scale, scale, INTER_LINEAR);
        imgToShow1 = fit_into_cv(imgToShow1);
        img1Size = imgToShow1.size();
        cout << "Source width:" << image1.size() << " ,Scale:" << scale <<  ", Width: " << img1Size << endl;
        imgToShow1.copyTo(cavan(Range(0, img1Size.height), Range(0, img1Size.width)));
    }

    // Scale Image 2
    auto img2Size = image2.size();
    if (img2Size.height > img2Size.width)
    {
        auto scale = PREVIEW_HEIGHT / static_cast<double>(img2Size.height);
        resize(imgToShow2, imgToShow2, Size(), scale, scale, INTER_LINEAR);
        imgToShow2 = fit_into_cv(imgToShow2);
        img2Size = imgToShow2.size();
        imgToShow2.copyTo(cavan(Range(0, img2Size.height), Range(HALF_WIDTH, HALF_WIDTH + img2Size.width)));
    } else
    {
        auto scale = HALF_WIDTH / static_cast<double>(img2Size.width);
        resize(imgToShow2, imgToShow2, Size(), scale, scale, INTER_LINEAR);
        imgToShow2 = fit_into_cv(imgToShow2);
        img2Size = imgToShow2.size();
        imgToShow2.copyTo(cavan(Range(0, img2Size.height), Range(HALF_WIDTH, HALF_WIDTH + img2Size.width)));
    }

    imshow(WindowName, cavan);
    waitKey(0);

}

void show2_and_wait(const Mat& image1, const Mat& image2)
{
    show2_and_wait(
        to_rgb(image1),
        to_rgb(image2),
        CV_8UC3);
}

int coinA()
{
    // Part A
    Mat coinsA = imread(DATA_PATH + "CoinsA.png", IMREAD_ANYCOLOR);
    // show_and_wait(coinsA);
    cout << coinsA.type() << endl;
    Mat coinsAGray;
    cvtColor(coinsA, coinsAGray, cv::COLOR_RGB2GRAY);
    cout << coinsA.type() << "|" << coinsAGray.type() << endl;

    // show2_and_wait(coinsA, coinsAGray);

    Mat coinsAChn[3], coinsAGrayChn[3];
    split(coinsA, coinsAChn);
    split(coinsAGray, coinsAGrayChn);

    // red
    // show2_and_wait(coinsAChn[0], coinsAGrayChn[0]);
    // green
    show2_and_wait(coinsA, coinsAChn[1]);
    // blue
    // show2_and_wait(coinsAChn[2], coinsAGrayChn[0]);

    /*****************
     * THRESHOLDING
     ****************/
    Mat thres1, thres2;
    /* for (int i = 20; i < 200; i += 10)
    {
        threshold(coinsAChn[2], thres, i, 255, THRESH_BINARY);
        show2_and_wait(thres * 255, coinsAChn[1]);
    } */
    // Compare Thresholds
    /* for (int i = 20; i < 150; i += 20)
    {
        cout << "Threshold: " << i << endl;
        threshold(coinsAChn[1], thres1, i, 255, THRESH_BINARY);
        threshold(coinsAChn[1], thres2, i, 255, THRESH_TOZERO);
        show2_and_wait(thres1, thres2);
    } */

    /* for (int i = 20; i < 200; i += 10)
    {
        threshold(coinsAChn[2], thres, i, 255, THRESH_BINARY);
        show2_and_wait(thres * 255, coinsAChn[1]);
    } */

    // 45, 80, 90 green threshold look great
    Mat th60, th80, th45, otsu;
    threshold(coinsAChn[1], th60, 60, 255, THRESH_BINARY_INV);
    threshold(coinsAChn[1], th80, 80, 255, THRESH_BINARY_INV);
    // show2_and_wait(th45, th80);
    threshold(coinsAChn[1], th45, 45, 255, THRESH_BINARY_INV);
    threshold(coinsAChn[1], otsu, 10, 255, THRESH_OTSU);
    // show2_and_wait(th45, th80);

    /*****************
     * MORPHOLOGY
    ****************/

    int kernelSize = 2;
    Mat closed;
    Mat closeEl = getStructuringElement(MORPH_ELLIPSE, Size(2*kernelSize+1, 2*kernelSize+1), Point(kernelSize, kernelSize));
    morphologyEx(th45, closed, MORPH_CLOSE, closeEl, Point(-1, -1), 1);

    // show2_and_wait(closed, th45);
    Mat opened = closed.clone();
    Mat circleEl = getStructuringElement(MORPH_ELLIPSE, Size(2+1, 2+1), Point(1, 1));
    // Tested with multiple iteration, 2 gave the best results
    morphologyEx(opened, opened, MORPH_OPEN, circleEl, Point(-1, -1), 2);

    show2_and_wait(opened, closed);

    // Reuse same loop for CLOSE testing
    /* for (int i = 1; i < 3; i++)
    {
        cout << i << endl;
        Mat opened = closed.clone();
        Mat circleEl = getStructuringElement(MORPH_ELLIPSE, Size(2*i+1, 2*i+1), Point(i, i));
        morphologyEx(opened, opened, MORPH_OPEN, circleEl, Point(-1, -1), 2);

        show2_and_wait(opened, closed);
    } */

    /*****************
     * Blob Detection
    ****************/
    // Detector Parameter
    SimpleBlobDetector::Params params;
    params.filterByColor = false;
    params.minDistBetweenBlobs = 2;
    params.blobColor = 0;
    params.filterByArea = false;
    // params.minArea = 100;
    params.filterByCircularity = true;
    params.minCircularity = 0.8;
    params.filterByConvexity = true;
    params.minConvexity = 0.8;
    params.filterByInertia = true;
    params.filterByInertia = 0.8;

    auto blobDetector = SimpleBlobDetector::create();
    blobDetector->setParams(params);
    std::vector<KeyPoint> keypoints;
    blobDetector->detect(opened, keypoints);
    if (keypoints.empty())
    {
        params.blobColor = 255;
        blobDetector->setParams(params);
        blobDetector->detect(opened, keypoints);
    }
    cout << "Found Points: " << keypoints.size() << endl;
    // Mat markings;
    // drawKeypoints(coinsA, keypoints, markings, Scalar(0, 255, 0), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);

    Mat detectedBlobs = coinsA.clone();
    for (const auto &kp : keypoints)
    {
        auto x = static_cast<int>(kp.pt.x);
        auto y = static_cast<int>(kp.pt.y);
        auto r = static_cast<int>(kp.size) / 2;
        circle(detectedBlobs, Point(x, y), 5, Scalar(255, 0, 0), -1);
        circle(detectedBlobs, Point(x, y), r, Scalar(0, 255, 0), 2);
    }

    show2_and_wait(detectedBlobs, opened);

    /*****************
     * CCA
    ****************/
    // invert image
    Mat inverted;
    bitwise_not(opened, inverted);
    show2_and_wait(inverted, opened);

    Mat ccaLabels;
    int nComponents = connectedComponents(inverted, ccaLabels);
    cout << "Components: " << nComponents << endl;

    Mat imLabels = ccaLabels.clone();
    Point minLoc, maxLoc;
    double minVal, maxVal;
    minMaxLoc(imLabels, &minVal, &maxVal, &minLoc, &maxLoc);

    // Normalize
    show2_and_wait(imLabels == 1, imLabels == 2);
    imLabels = 255 * (imLabels - minVal) / (maxVal - minVal);
    imLabels.convertTo(imLabels, CV_8U);
    Mat imColorMap;
    applyColorMap(imLabels, imColorMap, COLORMAP_HSV);
    show2_and_wait(imColorMap, opened);

    /*****************
     * Conture Detection
    ****************/
    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;
    Mat detectedContours = coinsA.clone();
    findContours(opened, contours, hierarchy, RETR_LIST, CHAIN_APPROX_SIMPLE);

    int maxIndex, maxArea = 0;
    for (int i = 0; i < contours.size(); i++)
    {
        auto area = contourArea(contours[i]);
        if (area > maxArea)
        {
            maxArea = static_cast<int>(area);
            maxIndex = i;
        }

        cout << i << " AREA: "<< contourArea(contours[i]) << endl;
    }
    // drawContours(detectedContours, contours, -1, Scalar(0, 255, 0), 1);
    Point2f center;
    float radius;
    for (int i = 0; i < contours.size(); i++)
    {
        if (i == maxIndex)
            continue;
        auto M = moments(contours[i]);
        auto x = int(M.m10 / static_cast<double>(M.m00));
        auto y = int(M.m01 / static_cast<double>(M.m00));
        circle(detectedContours, Point(x, y), 5, Scalar(255, 0, 0), -1);
        putText(detectedContours, to_string(i + 1), Point(x + 10, y-10), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 255, 255));
        minEnclosingCircle(contours[i], center, radius);
        circle(detectedContours, center, radius, Scalar(0, 255, 0), 2);
    }

    show2_and_wait(detectedContours, detectedBlobs);
    return 0;
}

void coinB()
{
    // Part A
    Mat coinsB = imread(DATA_PATH + "CoinsB.png", IMREAD_ANYCOLOR);
    // show_and_wait(coinsA);
    cout << coinsB.type() << endl;
    Mat coinsBGray;
    cvtColor(coinsB, coinsBGray, cv::COLOR_RGB2GRAY);
    cout << coinsB.type() << "|" << coinsBGray.type() << endl;

    // show2_and_wait(coinsA, coinsAGray);

    Mat coinsBChn[3], coinsBGrayChn[3];
    split(coinsB, coinsBChn);
    // split(coinsBGray, coinsBGrayChn);

    // red
    show2_and_wait(coinsB, coinsBChn[0]);
    // green
    // show2_and_wait(coinsB, coinsBChn[1]);
    // blue
    // show2_and_wait(coinsB, coinsBChn[2]);

    /********************
     * Thresholds
     ********************/

    /*****************
     * THRESHOLDING
     ****************/
    int channel = 0;
    /* Mat thres1, thres2;
    for (int i = 60; i < 120; i += 5)

    {
        threshold(coinsBChn[channel], thres1, i, 255, THRESH_BINARY);
        putText(thres1, to_string(i), Point(200, 400), FONT_HERSHEY_COMPLEX, 20, Scalar(0, 0, 0));
        show2_and_wait(thres1, coinsBChn[channel]);
    } */

    // Compare Thresholds
    /* for (int i = 20; i < 150; i += 20)
    {
        cout << "Threshold: " << i << endl;
        threshold(coinsAChn[1], thres1, i, 255, THRESH_BINARY);
        threshold(coinsAChn[1], thres2, i, 255, THRESH_TOZERO);
        show2_and_wait(thres1, thres2);
    } */

    /* for (int i = 20; i < 200; i += 10)
    {
        threshold(coinsAChn[2], thres, i, 255, THRESH_BINARY);
        show2_and_wait(thres * 255, coinsAChn[1]);
    } */

    // 45, 80, 90 green threshold look great
    int thres = 90;
    Mat thresImg, otsu;
    threshold(coinsBChn[channel], thresImg, thres, 255, THRESH_BINARY_INV);
    threshold(coinsBChn[channel], otsu, 10, 255, THRESH_OTSU);
    show2_and_wait(thresImg, coinsB);
    // show2_and_wait(otsu, coinsB);
    /*****************
       * MORPHOLOGY
      ****************/

    int kernelSize = 10;
    Mat closed;
    // Try to remove Circular Shape from inner Holes
    Mat closeEl = getStructuringElement(MORPH_RECT, Size(2*kernelSize+1, 2*kernelSize+1), Point(kernelSize, kernelSize));
    morphologyEx(thresImg, closed, MORPH_CLOSE, closeEl, Point(-1, -1), 3);

    show2_and_wait(closed, thresImg);

    // Mat opened;
    // morphologyEx(thresImg, opened, MORPH_OPEN, closeEl, Point(-1, -1), 3);

    // show2_and_wait(opened, thresImg);

    // Reuse same loop for CLOSE testing
    /* for (int i = 1; i < 3; i++)
    {
        cout << i << endl;
        Mat opened = closed.clone();
        Mat circleEl = getStructuringElement(MORPH_ELLIPSE, Size(2*i+1, 2*i+1), Point(i, i));
        morphologyEx(opened, opened, MORPH_OPEN, circleEl, Point(-1, -1), 2);

        show2_and_wait(opened, closed);
    } */

    /*****************
     * Blob Detection
    ****************/
    // Detector Parameter
    SimpleBlobDetector::Params params;
    params.filterByColor = false;
    params.minDistBetweenBlobs = 2;
    params.blobColor = 0;
    params.filterByArea = true;
    params.minArea = 100000;
    params.maxArea = 600000;
    params.filterByCircularity = false;
    params.minCircularity = 0.8;
    params.filterByConvexity = false;
    params.minConvexity = 0.7;
    params.filterByInertia = false;
    params.filterByInertia = 0.8;

    auto blobDetector = SimpleBlobDetector::create();
    blobDetector->setParams(params);
    std::vector<KeyPoint> keypoints;
    blobDetector->detect(closed, keypoints);
    if (keypoints.empty())
    {
        throw runtime_error("No keypoints found");
    }
    cout << "Found Points: " << keypoints.size() << endl;
    /*
    Mat markings;
    drawKeypoints(coinsB, keypoints, markings, Scalar(0, 255, 0), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
    show2_and_wait(markings, coinsB);
    */

    Mat detectedBlobs = coinsB.clone();
    for (const auto &kp : keypoints)
    {
        auto x = static_cast<int>(kp.pt.x);
        auto y = static_cast<int>(kp.pt.y);
        auto r = static_cast<int>(kp.size) / 2;
        circle(detectedBlobs, Point(x, y), 10, Scalar(255, 0, 0), -1);
        circle(detectedBlobs, Point(x, y), r, Scalar(0, 0, 255), 5);
    }

    show2_and_wait(detectedBlobs, closed);

    /*****************
    * CCA
    ****************/
    // invert image
    Mat inverted;
    bitwise_not(closed, inverted);
    show2_and_wait(inverted, closed);

    Mat ccaLabels;
    int nComponents = connectedComponents(closed, ccaLabels);
    cout << "Components: " << nComponents << endl;

    Mat imLabels = ccaLabels.clone();
    Point minLoc, maxLoc;
    double minVal, maxVal;
    minMaxLoc(imLabels, &minVal, &maxVal, &minLoc, &maxLoc);

    // Normalize
    // show2_and_wait(imLabels == 1, imLabels == 2);
    imLabels = 255 * (imLabels - minVal) / (maxVal - minVal);
    imLabels.convertTo(imLabels, CV_8U);
    Mat imColorMap;
    applyColorMap(imLabels, imColorMap, COLORMAP_JET);
    show2_and_wait(imColorMap, closed);

    /*****************
    * Conture Detection
   ****************/
    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;
    Mat detectedContours = coinsB.clone();
    findContours(closed, contours, hierarchy, RETR_CCOMP, CHAIN_APPROX_TC89_KCOS);

    double areaMinThreshold = 10.;
    double areaMaxThreshold = 10;
    int maxIndex, maxArea = 0;
    vector<int> smallAreas;
    for (int i = 0; i < contours.size(); i++)
    {
        auto area = contourArea(contours[i]);
        if (area <= areaMinThreshold)
        {
            smallAreas.push_back(i);
        } else if (area > maxArea)
        {
            maxArea = static_cast<int>(area);
            maxIndex = i;
        }

        cout << i << " AREA: "<< contourArea(contours[i]) << endl;
    }

    // drawContours(detectedContours, contours, -1, Scalar(0, 255, 0), 1);
    Point2f center;
    float radius;
    for (int i = 0; i < contours.size(); i++)
    {
        // if (i == maxIndex)
        //     continue;
        if (find(smallAreas.begin(), smallAreas.end(), i) != smallAreas.end())
            continue;

        // cout << hierarchy[i][0] << " " << hierarchy[i][1] << " " << hierarchy[i][2] << " " << hierarchy[i][3] << endl;

        // Only highlight outer contures
        if (hierarchy[i][3] != -1)
            continue;

        auto M = moments(contours[i]);
        auto x = int(M.m10 / static_cast<double>(M.m00));
        auto y = int(M.m01 / static_cast<double>(M.m00));
        circle(detectedContours, Point(x, y), 5, Scalar(255, 0, 0), -1);
        putText(detectedContours, to_string(i + 1), Point(x + 10, y-10), FONT_HERSHEY_SIMPLEX, 5, Scalar(0, 255, 255));
        minEnclosingCircle(contours[i], center, radius);
        circle(detectedContours, center, radius, Scalar(0, 255, 0), 10);
    }

    show2_and_wait(detectedContours, detectedBlobs);
}

int main()
{
    namedWindow(WindowName);

    // coinA();

    coinB();
}