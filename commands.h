

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
    SimpleAnomalyDetector *sad;
    std::vector<AnomalyReport> *anomalyReport;

public:
    Command(DefaultIO *dio) : dio(dio) {}

    virtual void execute() = 0;

    virtual ~Command() {}

    std::string getDescription() {
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
        float newThreshold;
        dio->write("the current correlation threshold is" + std::to_string(sad->getThreshold()));
        dio->read(&newThreshold);
        while (newThreshold < 0 || newThreshold > 1) {
            dio->write("please choose a value between 0 and 1");
            dio->write("the current correlation threshold is" + std::to_string(sad->getThreshold()));
            dio->read(&newThreshold);
        }
        sad->setThreshold(newThreshold);
    }
};

class detectCommand : public Command {
public:
    detectCommand(DefaultIO dio) : Command(&dio) {
        description = "3. detect anomalies";
    };

    void execute() override {
        TimeSeries train("train.csv");
        TimeSeries test("test.csv");
        sad->learnNormal(train);
        *anomalyReport = sad->detect(test);
        dio->write("anomaly detection complete");
    }
};

class resultsCommand : public Command {
public:
    resultsCommand(DefaultIO dio) : Command(&dio) {
        description = "4. display results";
    };


    void execute() override {
        for(AnomalyReport report:*anomalyReport){
            dio->write(std::to_string(report.timeStep)+"\t"+  report.description);
        }
        dio->write("done");
    }
};



// open the reading file





#endif /* COMMANDS_H_ */
