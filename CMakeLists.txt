cmake_minimum_required(VERSION 3.20)
project(ass1)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(ass1
        main.cpp
        SimpleAnomalyDetection.cpp
        SimpleAnomalyDetection.h
        anomaly_detection_util.cpp
        anomaly_detection_util.h
        TimeSeries.cpp
        TimeSeries.h)
