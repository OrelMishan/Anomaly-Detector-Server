

#ifndef COMMANDS_H_
#define COMMANDS_H_

#include<iostream>
#include <string.h>
# include <filesystem>
#include <fstream>
#include <vector>
#include "HybridAnomalyDetector.h"

using namespace std;


class DefaultIO {
public:
    virtual string read() = 0;

    virtual void write(string text) = 0;

    virtual void write(float f) = 0;

    virtual void read(float *f) = 0;

    virtual ~DefaultIO() {}

    // you may add additional methods here
};

// you may add here helper classes


// you may edit this class
class Command {
protected:
    std::string description;
    DefaultIO *dio;
public:
    Command(DefaultIO *dio) : dio(dio) {}
    virtual void execute() = 0;
    virtual ~Command() {}
    std:: string getDescription(){
        return description;
    };
};

class uploadCommand : public Command {
    void getFile(std::string readType) {
        dio->write("Please upload your local " + readType + "file.");
        std::ifstream fin;
        std::string line;
        ofstream csv(readType + ".csv");
        line = dio->read();
        while (line != "done") {
            csv << line << endl;
            line = dio->read();
        }
        dio->write("Upload complete");
    }
public:
    uploadCommand(DefaultIO dio) : Command(&dio) {
        description = "1. upload a time series csv file";
    };
    void execute() override {
        getFile("train");
        getFile("test");
    }
};

class settingsCommand : public Command {


public:
    settingsCommand(DefaultIO dio) : Command(&dio) {
        description = "2. algorithm settings";
    };
    void execute() override {
        
    }

}



// open the reading file





#endif /* COMMANDS_H_ */
