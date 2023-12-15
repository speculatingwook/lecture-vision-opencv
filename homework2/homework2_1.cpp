//
// Created by Yoon BeongWook on 2023/10/04.
//
//
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

Mat src, dst, redChannel, greenChannel, blueChannel;  // 이미지와 각 채널에 대한 Mat 객체 선언
int initialPos = 50; // 초기값 설정

// 각 채널의 밝기 값을 저장할 변수 선언
int redBrightness = 50;
int greenBrightness = 50;
int blueBrightness = 50;

// 함수 원형 선언
void updateChannelsAndDisplay(int, void*);
void onContrastChange(int, void*);

int homework2_1() {
    // 이미지 파일을 읽어옴
    std::string imagePath = "../images/Lenna.bmp";
    src = imread(imagePath, IMREAD_COLOR);

    // 이미지가 비어있는 경우 오류 메시지를 출력, 프로그램 종료
    if (src.empty()) {
        cerr << "Image load failed!" << endl;
        return -1;
    }

    // 창 생성
    namedWindow("Red Channel");
    namedWindow("Green Channel");
    namedWindow("Blue Channel");
    namedWindow("Adjusted Image");

    // 트랙바를 생성, 밝기 조절과 대비 조절을 위한 변수 연결
    createTrackbar("Red Brightness", "Red Channel", &redBrightness, 100, updateChannelsAndDisplay);
    createTrackbar("Green Brightness", "Green Channel", &greenBrightness, 100, updateChannelsAndDisplay);
    createTrackbar("Blue Brightness", "Blue Channel", &blueBrightness, 100, updateChannelsAndDisplay);
    createTrackbar("Contrast", "Adjusted Image", &initialPos, 100, onContrastChange);

    // 초기화된 함수를 호출, 이미지 업데이트와 디스플레이
    updateChannelsAndDisplay(0, nullptr);

    // 사용자의 키 입력 대기
    waitKey(0);

    // 생성한 창을 모두 닫음
    destroyAllWindows();

    return 0;
}

// 이미지 채널을 업데이트하고 디스플레이하는 함수
void updateChannelsAndDisplay(int, void*) {
    Mat channels[3];
    split(src, channels);  // 이미지를 RGB 채널로 분할

    // 각 채널에 밝기 조절 적용
    channels[0] = channels[0] + blueBrightness - 50;
    channels[1] = channels[1] + greenBrightness - 50;
    channels[2] = channels[2] + redBrightness - 50;

    // 채널을 다시 합성하여 조절된 이미지 생성
    merge(channels, 3, dst);

    // 대비 조절을 위한 알파 값을 계산하고 이미지 적용
    double alpha = 1 + (initialPos - 50) / 100.0;
    dst = dst * alpha;

    // 개별 채널을 업데이트하고 디스플레이
    blueChannel = channels[0];
    greenChannel = channels[1];
    redChannel = channels[2];

    imshow("Red Channel", redChannel);
    imshow("Green Channel", greenChannel);
    imshow("Blue Channel", blueChannel);
    imshow("Adjusted Image", dst);
}

// 대비 변경 트랙바 콜백 함수
void onContrastChange(int, void*) {
    updateChannelsAndDisplay(0, nullptr);  // 이미지를 업데이트하고 디스플레이
}
