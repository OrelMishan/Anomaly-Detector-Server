//
// Created by אוראל משען on 01/11/2021.
//
#include "TimeSeries.h"
#include "TimeSeries.cpp"

int main(int argc,char** argv) {
    TimeSeries *t = new TimeSeries("C:\\Users\\Public\\ass1\\test_time_series.csv");
    t->print();
}


