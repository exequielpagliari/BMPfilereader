cmake_minimum_required(VERSION 3.10)

project(BMPReader)

# Define the source directory to be copied
set(SOURCE_DATA_DIR "${CMAKE_CURRENT_SOURCE_DIR}/imgTest")

# Define the destination directory within the build directory
set(DESTINATION_DATA_DIR "${CMAKE_CURRENT_BINARY_DIR}/")

# Copy the entire 'data' directory and its contents
file(COPY "${SOURCE_DATA_DIR}" DESTINATION "${DESTINATION_DATA_DIR}")

add_executable(BMPReader main.cpp)
