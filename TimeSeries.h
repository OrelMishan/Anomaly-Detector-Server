//
// Created by user on 27/10/2021.
//

#ifndef ASS1_TIMESERIES_H
#define ASS1_TIMESERIES_H

class TimeSeries{
    std::vector<std::vector<std::string>> table;
public:
    TimeSeries(const std::string&);
    void printTable();
};
#endif //ASS1_TIMESERIES_H
