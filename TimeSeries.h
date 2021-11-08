

#ifndef ASS1_TIMESERIES_H
#define ASS1_TIMESERIES_H

#include <vector>
#include <string>

class TimeSeries{
    std::vector<std::vector<std::string>> table;
    void putKeys(std::string line) ;
    void putValues(std::string line) ;
public:
    explicit TimeSeries(const std::string&);
    void printTable();
    std::vector<std::vector<std::string>> getTable() const;
    float **getFloatArrays();
    int getNumOfValues();
};


#endif //ASS1_TIMESERIES_H
