cmake_minimum_required(VERSION 3.10)

project(CV_LEARN)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)


set(OpenCV_DIR C:/Users/niuti/Documents/Dev/OpenCV/opencv/build)
find_package(OpenCV REQUIRED)

add_executable(${PROJECT_NAME} src/test.cpp)
add_executable(how_to_scan_images src/how_to_scan_images.cpp)
add_executable(mat_mask_operations src/mat_mask_operations.cpp)

target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})
target_link_libraries(how_to_scan_images ${OpenCV_LIBS})
target_link_libraries(mat_mask_operations ${OpenCV_LIBS})


