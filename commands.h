//Name: Noam Tzuberi ID:313374837
//Name: Orel Mishan ID:316551092

#ifndef COMMANDS_H_
#define COMMANDS_H_

#include<iostream>
#include <string>
#include <fstream>
#include <vector>
#include "HybridAnomalyDetector.h"


class DefaultIO {
public:
    virtual string read() = 0;

    virtual void write(std::string text) = 0;

    virtual void write(float f) = 0;

    virtual void read(float *f) = 0;

    virtual ~DefaultIO() = default;

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
    int *linesNumber;


public:
    Command(DefaultIO *dio, SimpleAnomalyDetector *sad, std::vector<AnomalyReport> *anomalyReport, int *linesNumber) :
            dio(dio), sad(sad), anomalyReport(anomalyReport), linesNumber(linesNumber) {}

    virtual void execute() = 0;

    virtual ~Command() {}

    std::string getDescription() {
        return description;
    };
};

class uploadCommand : public Command {
    void getFile(std::string readType) {
        dio->write("Please upload your local " + readType + " CSV file.\n");
        std::ifstream fin;
        std::string line;
        ofstream csv(readType + ".csv");
        line = dio->read();
        while (line != "done") {
            csv << line << endl;
            line = dio->read();
        }
        dio->write("Upload complete.\n");
        csv.close();
    }

public:
    uploadCommand(DefaultIO *dio, SimpleAnomalyDetector *sad, std::vector<AnomalyReport> *anomalyReport,
                  int *linesNumber) : Command(dio, sad, anomalyReport, linesNumber) {
        description = "1.upload a time series csv file";
    };

    void execute() override {
        getFile("train");
        getFile("test");
    }
};

class settingsCommand : public Command {
public:
    settingsCommand(DefaultIO *dio, SimpleAnomalyDetector *sad, std::vector<AnomalyReport> *anomalyReport,
                    int *linesNumber) : Command(dio, sad, anomalyReport, linesNumber) {
        description = "2.algorithm settings";

    };

    void execute() override {
        float newThreshold;
        dio->write("The current correlation threshold is ");
        dio->write(sad->getThreshold());
        dio->write("\n");
        dio->write("Type a new threshold\n");
        dio->read(&newThreshold);

        while (newThreshold < 0 || newThreshold > 1) {
            dio->write("please choose a value between 0 and 1\n");
            dio->write("The current correlation threshold is ");
            dio->write(sad->getThreshold());
            dio->write("\n");
            dio->read(&newThreshold);
        }
        sad->setThreshold(newThreshold);
    }
};

class detectCommand : public Command {
public:
    detectCommand(DefaultIO *dio, SimpleAnomalyDetector *sad, std::vector<AnomalyReport> *anomalyReport,
                  int *linesNumber) : Command(dio, sad, anomalyReport, linesNumber) {
        description = "3.detect anomalies";
    }


    void execute() override {
        TimeSeries train("train.csv");
        TimeSeries test("test.csv");
        *linesNumber = test.getNumOfValues();
        sad->learnNormal(train);
        *anomalyReport = sad->detect(test);
        dio->write("anomaly detection complete.\n");
    }
};

class resultsCommand : public Command {
public:
    resultsCommand(DefaultIO *dio, SimpleAnomalyDetector *sad, std::vector<AnomalyReport> *anomalyReport,
                   int *linesNumber) : Command(dio, sad, anomalyReport, linesNumber) {
        description = "4.display results";
    }


    void execute() override {
        for (correlatedFeatures c: sad->getNormalModel()) {
            for (const AnomalyReport &report: *anomalyReport) {
                if (report.description == c.feature1 + "-" + c.feature2) {
                    dio->write(report.timeStep);
                    dio->write("\t" + report.description + "\n");
                }
            }
        }
        dio->write("Done.\n");
    }
};

class analyzeCommand : public Command {
    int getTimeFrames() {
        int count = 1;
        int numReports = anomalyReport->size() ;
        int i;
        for ( i = 2; i <numReports; i++) {
            if (anomalyReport->at(i-1).timeStep + 1 != anomalyReport->at(i).timeStep) {
                count++;
            }
        }
        if (anomalyReport->at(0).timeStep + 1 != anomalyReport->at( 1).timeStep) {
            count++;
        }
        return count;
    }

public:
    analyzeCommand(DefaultIO *dio, SimpleAnomalyDetector *sad, std::vector<AnomalyReport> *anomalyReport,
                   int *linesNumber) : Command(dio, sad, anomalyReport, linesNumber) {
        description = "5.upload anomalies and analyze results";
    };

    void execute() override {
        dio->write("Please upload your local anomalies file.\n");
        int clientReporting = 0;
        int positive = 0;
        std::string line = dio->read();
        size_t pos;
        std::string delim = ",";

        // the match reporting
        float TP = 0;
        float FP = getTimeFrames();

        while (line != "done") {
            // the amount of reporting
            positive++;
            pos = line.find(delim);
            int start = stoi(line.substr(0, pos));
            line = line.erase(0, pos + 1);
            int end = stoi(line);
            clientReporting += end - start + 1;
            int count = 0;
            int numReport = anomalyReport->size();
            for (int i = 0; i < numReport; i++) {
                if (anomalyReport->at(i).timeStep >= start && anomalyReport->at(i).timeStep <= end) {
                        count++;
                }
            }
            if (count) {
                TP++;
                FP--;
            }

            line = dio->read();
        }
        dio->write("Upload complete.\n");
        dio->write("True Positive Rate: ");
        dio->write(TP / positive);
        dio->write("\nFalse Positive Rate: ");

        dio->write((int)(1000.0*FP/(float )(*linesNumber-clientReporting))/1000.0f);
        dio->write("\n");
    }
};

class exitCommand : public Command {
public:
    exitCommand(DefaultIO *dio, SimpleAnomalyDetector *sad, std::vector<AnomalyReport> *anomalyReport, int *linesNumber)
            : Command(dio, sad, anomalyReport, linesNumber) {
        description = "6.exit";
    }

    void execute() override {}
};




// open the reading file





#endif /* COMMANDS_H_ */
