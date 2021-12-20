

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
    int linesNumber;


public:
    Command(DefaultIO *dio, SimpleAnomalyDetector *sad, std::vector<AnomalyReport> *anomalyReport) : dio(dio), sad(sad),
                                                                                                     anomalyReport(anomalyReport) {}
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
        csv.close();
    }

public:
    uploadCommand(DefaultIO *dio, SimpleAnomalyDetector *sad, vector<AnomalyReport> anomalyReport) : Command(&dio,
                                                                                                             sad,
                                                                                                             anomalyReport) {
        description = "1.upload a time series csv file";
    };

    void execute() override {
        getFile("train");
        getFile("test");
    }
};

class settingsCommand : public Command {
public:
    settingsCommand(DefaultIO dio, SimpleAnomalyDetector *sad, std::vector<AnomalyReport> *anomalyReport) : Command(
            &dio, sad, anomalyReport) {
        description = "2.algorithm settings";

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
    detectCommand(DefaultIO dio, SimpleAnomalyDetector *sad, std::vector<AnomalyReport> *anomalyReport) : Command(&dio,sad,anomalyReport) {
        description = "3.detect anomalies";
    }


    void execute() override {
        TimeSeries train("train.csv");
        TimeSeries test("test.csv");
        linesNumber = test.getNumOfValues();
        sad->learnNormal(train);
        *anomalyReport = sad->detect(test);
        dio->write("anomaly detection complete");
    }
};

class resultsCommand : public Command {
public:
    resultsCommand(DefaultIO dio, SimpleAnomalyDetector *sad, std::vector<AnomalyReport> *anomalyReport) : Command(&dio,sad,anomalyReport){
        description = "4.display results";
    }


    void execute() override {
        for (const AnomalyReport& report: *anomalyReport) {
            dio->write(std::to_string(report.timeStep) + "\t" + report.description);
        }
        dio->write("done");
    }
};

class analyzeCommand : public Command {
public:
    analyzeCommand(DefaultIO dio, SimpleAnomalyDetector *sad, std::vector<AnomalyReport> *anomalyReport) : Command(&dio,sad,anomalyReport){
        description = "5.upload anomalies and analyze results";
    };

    void execute() override {
        dio->write("Please upload your local anomalies file.");
        int clientReporting = 0;
        int positive = 0;
        std::string line = dio->read();
        size_t pos;
        std::string delim = ",";

        // the match reporting
        float TP = 0;
        float FP = 0;
        while (line != "done") {
            // the amount of reporting
            positive++;


            pos = line.find(delim);
            int start = stoi(line.substr(0, pos));
            line = line.erase(0, pos + 1);
            int end = stoi(line);
            clientReporting += end - start + 1;
            bool isTrue = false;
            for (const AnomalyReport &report: *anomalyReport) {
                if (report.timeStep >= start || report.timeStep <= end) {
                    isTrue = true;
                    TP += 1;
                    break;
                }
            }
            if (!isTrue) {
                FP += 1;
            }
            line = dio->read();
        }
        dio->write("Upload complete");
        dio->write("True Positive Rate: " + std::to_string(TP / positive));
        dio->write("True Positive Rate: " + std::to_string(FP / linesNumber - clientReporting));
    }
};

class exitCommand : public Command {
public:
    exitCommand(DefaultIO dio, SimpleAnomalyDetector *sad, std::vector<AnomalyReport> *anomalyReport) : Command(&dio,sad,anomalyReport) {
        description = "6.exit";
    }
    void execute() override {
        exit(0);
    }
};




// open the reading file





#endif /* COMMANDS_H_ */
