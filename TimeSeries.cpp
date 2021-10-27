#include <iostream>
#include <map>
#include <vector>
#include <fstream>
#include<iostream>
#include<vector>
#include<sstream>
#include "TimeSeries.h"


class TimeSeries {

    std::map<std::string, std::vector<float>> table;

    void putKeys(std::string line) {
        std::string tmp;
        size_t counter = 0;
        while ((counter = line.find(',') != std::string::npos)) {
            tmp = line.substr(0, counter);
            table[tmp] = {};
            line.erase(0, counter + 1);
        }
    }
    void putValues(std::string line){
            std::string tmp;
            size_t counter = 0;
            for (auto it = table.begin(); it != table.end(); ++it) {
                counter = line.find(',');
                tmp = line.substr(0, counter);
                it->second.push_back(std::stof(tmp));
                line.erase(0, counter + 1);
        }
    }
public:
    TimeSeries(std::string path) {
        // cre
        std::ifstream fin;
        std::string line, tmp;
        std::string comma = ",";
        fin.open(path);
        int i = 0;
        if (!fin.eof()) {
            fin >> line;
            putKeys(line);
        }
        while (!fin.eof()) {
            fin >> line;
            putValues(line);

            }
        }

    };





