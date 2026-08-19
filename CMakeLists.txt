cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_COMPILER "C:/msys64/ucrt64/bin/g++.exe")
project(QRCodeGenerator CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(qrcode_app src/main.cpp src/QR_Generator.cpp)
target_include_directories(qrcode_app PRIVATE include/)