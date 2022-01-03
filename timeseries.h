//Name: Noam Tzuberi ID:313374837
//Name: Orel Mishan ID:316551092

#ifndef ASS1_TIMESERIES_H
#define ASS1_TIMESERIES_H

#include <vector>
#include <string>

class timeseries {
    std::vector<std::vector<std::string>> table;

    void putKeys(std::string line);

    void putValues(std::string line);

public:
    explicit timeseries(const std::string &);

//    void printTable();
    std::vector<std::vector<std::string>> getTable() const;

    float **getFloatArrays() const;

    int getNumOfValues() const;

    std::string getName(int i) const;
};


#endif //ASS1_TIMESERIES_H
