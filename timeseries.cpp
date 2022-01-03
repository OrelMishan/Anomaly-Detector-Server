//Name: Noam Tzuberi ID:313374837
//Name: Orel Mishan ID:316551092

#include <fstream>
#include <vector>
#include <iostream>
#include "timeseries.h"

void TimeSeries::putKeys(std::string line) {

    // tmp- the name of current column
    std::string tmp;
    // the size of the column(= the name of the variables)
    size_t counter;

    // loop for the first line
    while (line.length() != 0) {

        // looking for the ","
        counter = line.find(',');

        // taking the part from o to the place of the comma(",")
        tmp = line.substr(0, counter);

        // creating vector of strings
        std::vector<std::string> toAdd;

        // push the name of the column to the start
        toAdd.push_back(tmp);

        // push the vector to the table
        table.push_back(toAdd);

        // if the counter in the end of the line
        if (counter == std::string::npos) {
            // putting the counter in the end of line
            counter = line.length() - 1;
        }

        // delete the part of the line that already used
        line.erase(0, counter + 1);
    }
}

void TimeSeries::putValues(std::string line) {

    // taking the numbers(values) as string
    std::string tmp;

    // the number of the columns
    size_t counter;

    // loop for all the vectors on the table
    for (auto &it: table) {

        //  find the comma
        counter = line.find(',');

        // take the string until the comma
        tmp = line.substr(0, counter);

        // push the value to vector
        it.push_back(tmp);

        // delete the part that already used
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

std::vector<std::vector<std::string>> TimeSeries::getTable() const {
    return table;
}

float *phraseToFloat(std::vector<std::string> vec) {
    // creating the floats array
    float *arr = new float[vec.size() - 1];

    //loop for all the values
    for (int i = 1; i < vec.size(); i++) {
        arr[i - 1] = std::stof(vec[i]);
    }
    return arr;
}

float ** TimeSeries::getFloatArrays() const {
    // create arrays of float
    float**arr = new float*[table.size()];

    // for all the vectors in the table
    for (int i=0;i<table.size();i++) {

        arr[i] = phraseToFloat(table[i]);
    }
    // return the array
    return arr;
}

int TimeSeries::getNumOfValues() const{
    // the number of the vectors- the length of the column
    return table[0].size()-1;
}

std::string TimeSeries::getName(int i) const {
    // the name of the column
    return table.at(i).at(0);
}








