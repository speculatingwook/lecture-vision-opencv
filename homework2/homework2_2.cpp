////
//// Created by Yoon BeongWook on 2023/10/04.
////
//#include <opencv2/opencv.hpp>
//using namespace cv;
//
//Mat originalImage; // 원본 이미지
//Mat resultImage;   // 결과 이미지
//
//Rect rect; // 드래그한 사각형 영역
//
//bool isDragging = false;
//
//void onMouse(int event, int x, int y, int flags, void* userdata) {
//    if (event == EVENT_LBUTTONDOWN) {
//        isDragging = true;
//        rect.x = x;
//        rect.y = y;
//    }
//    else if (event == EVENT_MOUSEMOVE && isDragging) {
//        resultImage = originalImage.clone(); // 원본 이미지를 복사하여 결과 이미지 생성
//        rect.width = x - rect.x;
//        rect.height = y - rect.y;
//        rectangle(resultImage, rect, Scalar(0, 0, 255), 2); // 드래그 중인 사각형을 그림
//        imshow("Image", resultImage);
//    }
//    else if (event == EVENT_LBUTTONUP && isDragging) {
//        isDragging = false;
//        rect.width = x - rect.x;
//        rect.height = y - rect.y;
//
//        // OR 연산을 통해 결과 이미지 생성
//        bitwise_or(originalImage, resultImage, resultImage);
//        Mat roi = resultImage(rect);
//        bitwise_not(roi, roi);
//
//        imshow("Image", resultImage);
//    }
//}
//
//int homework2_2() {
//    std::string imagePath = "../images/Lenna.bmp";
//    originalImage = imread(imagePath);
//
//    if (originalImage.empty()) {
//        std::cerr << "이미지를 읽을 수 없습니다." << std::endl;
//        return -1;
//    }
//
//    resultImage = originalImage.clone();
//
//    namedWindow("Image");
//    setMouseCallback("Image", onMouse);
//
//    imshow("Image", originalImage);
//    waitKey(0);
//
//    return 0;
//}
