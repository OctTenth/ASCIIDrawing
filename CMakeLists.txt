cmake_minimum_required(VERSION 3.10)

project(ASCIIDrawing)

file(GLOB SRC_FILE "${PROJECT_SOURCE_DIR}/src/*.cpp" "${PROJECT_SOURCE_DIR}/src/*.hpp")

find_package(OpenCV CONFIG REQUIRED)

add_executable(ASCIIDrawing ${SRC_FILE})

target_link_libraries(${PROJECT_NAME} PRIVATE ${OpenCV_LIBS})