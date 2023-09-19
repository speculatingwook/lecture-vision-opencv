//
// Created by Yoon BeongWook on 2023/09/19.
//
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int homework1(void){
    cout << "Hello OpenCV " << CV_VERSION << endl;

    Mat img;
    img = imread("/Users/yoonbeongwook/CLionProjects/smart_vehicle_vision/Lenna.bmp");

    if (img.empty()) {
        cerr << "Image load failed!" << endl;
        return -1;
    }

    namedWindow("image");
    imshow("image", img);

    waitKey(0);
    return 0;
}