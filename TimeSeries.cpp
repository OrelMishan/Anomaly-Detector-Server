#include <fstream>
#include<sstream>
#include <map>
#include <vector>




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
    explicit TimeSeries(const std::string& path) {
        // define file, line
        std::ifstream fin;
        std::string line, tmp;
        // open the reading file
        fin.open(path);
        int i = 0;
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

    };





