cmake_minimum_required(VERSION 3.10)
project(smart_vehicle_vision)

# OpenCV 설정
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

set(cmake_cxx_standard 11)

add_executable(smart_vehicle_vision main.cpp
        homework2/homework2_1.cpp
        homework2/homework2_2.cpp
        homework3/homework3.cpp
        homework4/homwork4.cpp
)

# OpenCV 라이브러리 추가
# tell the build to include the headers from OpenCV
target_link_libraries(smart_vehicle_vision ${OpenCV_LIBS})