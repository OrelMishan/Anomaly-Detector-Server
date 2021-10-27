#include <fstream>
#include<sstream>
#include <map>
#include <vector>
#include <iostream>


class TimeSeries {

    std::map<std::string, std::vector<float>> table;

    void putKeys(std::string line) {
        std::string tmp;
        size_t counter;
        while ((counter = line.find(',') != std::string::npos)) {
            tmp = line.substr(0, counter);
            table[tmp] = {};
            line.erase(0, counter + 1);
        }
    }
    void putValues(std::string line){
            std::string tmp;
            size_t counter;
            for (auto & it : table) {
                counter = line.find(',');
                tmp = line.substr(0, counter);
                it.second.push_back(std::stof(tmp));
                line.erase(0, counter + 1);
        }
    }
public:
     TimeSeries(const std::string& path) {
        // define file, line
        std::ifstream fin;
        std::string line, tmp;
        // open the reading file
        fin.open(path);
        // put the keys in the map
        if (!fin.eof()) {
            fin >> line;
            putKeys(line);
        }
        // put the values in the map
        while (!fin.eof()) {
            fin >> line;
            putValues(line);

            }
        }
    void printTable() {
        for (auto & it : table) {
            std:: cout << it.first << ":" ;
        }
    }



};
int main(int argc,char** argv) {
    TimeSeries t = *new TimeSeries(argv[0]);
    t.printTable();
}





