//
// Created by Yoon BeongWook on 2023/12/13.
//
#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>

using namespace cv;
using namespace std;

struct MouseParams {
    vector<Point2f> points;
    Mat image;
};

void onMouse(int event, int x, int y, int flags, void* param) {
    if (event == EVENT_LBUTTONDOWN) {
        MouseParams* mouseParams = (MouseParams*)param;
        circle(mouseParams->image, Point(x, y), 3, Scalar(0, 255, 0), -1);
        imshow("Select Points", mouseParams->image);
        mouseParams->points.push_back(Point(x, y));

        if (mouseParams->points.size() == 4) {
            // Disable mouse event after 4 points are selected
            setMouseCallback("Select Points", NULL, NULL);
        }
    }
}

vector<Point2f> getPointsFromImage(const Mat& img) {
    MouseParams mouseParams;
    mouseParams.image = img.clone();

    namedWindow("Select Points");
    imshow("Select Points", mouseParams.image);

    setMouseCallback("Select Points", onMouse, &mouseParams);

    waitKey(0);
    destroyWindow("Select Points");

    return mouseParams.points;
}

cv::Mat getPerspectiveTransformMatrix(const vector<Point2f>& srcPoints) {
    vector<Point2f> dstPoints;
    dstPoints.push_back(Point2f(0, 0));
    dstPoints.push_back(Point2f(0, 1920));
    dstPoints.push_back(Point2f(1080, 0));
    dstPoints.push_back(Point2f(1080, 1920));

    return cv::getPerspectiveTransform(srcPoints, dstPoints);
}

int homework4() {
    std::string imagePath = "../images/setting.png"; // Replace with the path to an image for selecting points
    Mat image = imread(imagePath);

    if (image.empty()) {
        cout << "Image not found or unable to load!" << endl;
        return -1;
    }

    vector<Point2f> selectedPoints = getPointsFromImage(image);

    Point2f topLeft = selectedPoints[0];
    Point2f topRight = selectedPoints[2];
    Point2f bottomRight = selectedPoints[3];
    Point2f bottomLeft = selectedPoints[1];

    // 사다리꼴의 상단과 하단의 중심점을 찾습니다.
    Point2f topCenter((topLeft.x + topRight.x) / 2, (topLeft.y + topRight.y) / 2);
    Point2f bottomCenter((bottomLeft.x + bottomRight.x) / 2, (bottomLeft.y + bottomRight.y) / 2);

    float scale = 4; // 예를 들어 1.5로 설정

// 상단 점들의 좌표를 조정합니다.
    topLeft = (topLeft - topCenter) * scale + topCenter;
    topRight = (topRight - topCenter) * scale + topCenter;

// 하단 점들의 좌표를 조정합니다.
    bottomLeft = (bottomLeft - bottomCenter) * scale + bottomCenter;
    bottomRight = (bottomRight - bottomCenter) * scale + bottomCenter;


// 조정된 점들을 다시 selectedPoints에 저장합니다.
    selectedPoints[0] = topLeft;
    selectedPoints[2] = topRight;
    selectedPoints[3] = bottomRight;
    selectedPoints[1] = bottomLeft;




    if (selectedPoints.size() != 4) {
        cout << "Please select 4 points!" << endl;
        return -1;
    }

    Size transformedSize(1920, 1080); // Adjust size as needed
    Mat perspectiveMatrix = getPerspectiveTransformMatrix(selectedPoints);

    std::string videoPath = "../video/Blackbox.mp4"; // Replace with the path to the black box video
    VideoCapture cap(videoPath);
    if (!cap.isOpened()) {
        cout << "Error opening video file" << endl;
        return -1;
    }

    Mat frame, transformedFrame;
    while (true) {
        cap >> frame;
        if (frame.empty())
            break;

        warpPerspective(frame, transformedFrame, perspectiveMatrix, transformedSize);

        // Additional processing (e.g., lane detection, distance measurement) goes here

        imshow("Transformed Frame", transformedFrame);
        if (waitKey(30) == 27) // Exit on ESC key
            break;
    }

    cap.release();
    destroyAllWindows();

    return 0;
}
