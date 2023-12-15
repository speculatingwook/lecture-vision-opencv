//
// Created by Yoon BeongWook on 2023/11/19.
//
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

void setLabel(Mat& img, const vector<Point>& pts, const String& label, vector<Rect>& drawnRects) {
    Rect rc = boundingRect(pts);

    bool collision = false;
    for (const auto& rect : drawnRects) {
        if ((rc & rect).area() > 0) {
            collision = true;
            break;
        }
    }

    // 충돌이 없는 경우에만 라벨을 그림
    if (!collision) {
        rectangle(img, rc, Scalar(0, 255, 0), 3);
        drawnRects.push_back(rc); // 그려진 라벨 영역 추가
    }
}

/**
 *
 * @return 신호판을 인식하는 함수
 */
int homework3() {
    // 이미지 읽기
    std::string imagePath = "../images/traffic_sign.bmp";
    Mat image = imread(imagePath);
    Mat gray, bin, morph;

    if (image.empty()) {
        cout << "이미지를 불러올 수 없습니다." << endl;
        return -1;
    }

    // 흑백 이미지로 변환
    cvtColor(image, gray, COLOR_BGR2GRAY);

    // 이진화
    threshold(gray, bin, 120, 255, THRESH_BINARY | THRESH_OTSU);

    // 모폴로지 연산을 통해 불필요한 부분 제거
    Mat element = getStructuringElement(MORPH_RECT, Size(3, 3));
    morphologyEx(bin, morph, MORPH_CLOSE, element);

    // 외곽선 찾기
    vector<vector<Point>> contours;
    findContours(morph, contours, RETR_TREE, CHAIN_APPROX_SIMPLE);

    // 이미 그려진 라벨 영역들을 저장할 벡터
    vector<Rect> drawnRects;

    // 신호판 영역 찾기
    for (const auto& contour : contours) {
        double area = contourArea(contour);
        if (area > 1900 && area < 6000) { // 너무 작거나 큰 영역 제거
            vector<Point> approx;
            approxPolyDP(contour, approx, arcLength(contour, true) * 0.02, true);

            if (approx.size() == 5) {
                setLabel(image, contour, "OTHER", drawnRects);
            } else if (approx.size() == 3) {
                setLabel(image, contour, "TRI", drawnRects);
            } else if (approx.size() == 4) {
                setLabel(image, contour, "RECT", drawnRects);
            } else {
                double len = arcLength(contour, true);
                double area = contourArea(contour);
                double ratio = 4. * CV_PI * area / (len * len);

                if (ratio > 0.85) {
                    setLabel(image, contour, "CIR", drawnRects);
                }
            }
        }
    }

    // 결과 이미지 보기
    imshow("Detected Sign", image);
    waitKey(0);
    destroyAllWindows();

    return 0;
}