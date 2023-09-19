cmake_minimum_required(VERSION 3.10)
project(smart_vehicle_vision)

# OpenCV 설정
find_package(OpenCV REQUIRED)

set(CMAKE_CXX_STANDARD 17)

add_executable(smart_vehicle_vision main.cpp
        homework1/homework1.cpp)

# OpenCV 라이브러리 추가
target_link_libraries(smart_vehicle_vision ${OpenCV_LIBS})
