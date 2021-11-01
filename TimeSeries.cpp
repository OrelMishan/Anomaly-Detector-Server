#include <fstream>
#include<sstream>
#include <map>
#include <vector>
#include <iostream>
#include "TimeSeries.h"


     std::vector<std::vector<std::string>> table;

    void putKeys(std::string line) {
        std::string tmp;
        size_t counter;
        while ((counter = line.find(',') )!= std::string::npos) {
            tmp = line.substr(0, counter);
            std::vector<std::string> toAdd;
            toAdd.push_back(tmp);
            table.push_back(toAdd) ;
            line.erase(0, counter + 1);
        }
        std::vector<std::string> toAdd;
        toAdd.push_back(line);
        table.push_back(toAdd) ;


    }

    void putValues(std::string line) {
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
        if (!fin.is_open()){
            std::cout<<"bad"<<std::endl;
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
    void printTable(){
        int sizeVector= table.at(1).size();
        for(int i =0; i<sizeVector;i++){
            for(auto &it: table){
                std::cout<<it.at(i)<<":";
            }
            std::cout<<std::endl;
        }
    }

};





