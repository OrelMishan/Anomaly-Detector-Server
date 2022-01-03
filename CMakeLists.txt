cmake_minimum_required(VERSION 3.20)
project(ass1)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread" )

include_directories(.)


add_executable(ass1
        MainTrain.cpp
        SimpleAnomalyDetector.cpp
        SimpleAnomalyDetector.h
        anomaly_detection_util.cpp
        anomaly_detection_util.h
        HybridAnomalyDetector.h
        HybridAnomalyDetector.cpp
        minCircle.h
        minCircle.cpp
        commands.h
        CLI.h
        CLI.cpp
        TimeSeries.cpp
        TimeSeries.h
        Server.cpp
        Server.h)
