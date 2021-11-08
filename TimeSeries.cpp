#include <fstream>
#include <vector>
#include <iostream>
#include "TimeSeries.h"

void TimeSeries::putKeys(std::string line) {
    std::string tmp;
    size_t counter;
    while (line.length() != 0) {
        counter = line.find(',');
        tmp = line.substr(0, counter);
        std::vector<std::string> toAdd;
        toAdd.push_back(tmp);
        table.push_back(toAdd);
        if (counter == std::string::npos) {
            counter = line.length() - 1;
        }
        line.erase(0, counter + 1);
    }
}

void TimeSeries::putValues(std::string line) {
    std::string tmp;
    size_t counter;
    for (auto &it: table) {
        counter = line.find(',');
        tmp = line.substr(0, counter);
        it.push_back(tmp);
        line.erase(0, counter + 1);
    }

}

TimeSeries::TimeSeries(const std::string &path) {
    // define file, line
    std::ifstream fin;
    std::string line, tmp;
    // open the reading file
    fin.open(path);
    if (!fin.is_open()) {
        std::cout << "bad" << std::endl;
    }
    // put the keys in the map
    if (std::getline(fin, line)) {
        putKeys(line);
    }
    // put the values in the map
    while (std::getline(fin, line)) {
        putValues(line);
    }
    fin.close();
}

void TimeSeries::printTable() {
    int sizeVector = table.at(1).size();
    for (int i = 0; i < sizeVector; i++) {
        for (auto &it: table) {
            std::cout << it.at(i) << ":";
        }
        std::cout << std::endl;
    }
}

std::vector<std::vector<std::string>> TimeSeries::getTable() const {
    return table;
}

float *phraseToFloat(std::vector<std::string> vec) {
    float *arr = new float[vec.size() - 1];
    for (int i = 1; i < vec.size(); i++) {
        arr[i - 1] = std::stof(vec[1]);
    }
    return arr;
}

float **TimeSeries::getFloatArrays() {
    float**arr = new float*[table.size()];
    for (int i=0;i<table.size();i++) {
        arr[i] = phraseToFloat(table[i]);
    }
    return arr;
}

int TimeSeries::getNumOfValues(){
    return table[0].size()-1;
}






