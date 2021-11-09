#include "AnomalyDetector.h"
#include "SimpleAnomalyDetection.h"

#include <utility>
#include <iostream>

SimpleAnomalyDetector::SimpleAnomalyDetector() = default;;

float findMaxThreshold(Line line, float *pDouble, float *pDouble1, int size);

Point **points(float *x, float *y, int size) {
    Point **ptr = new Point*[size];
    for (int i = 0; i < size; i++) {
        ptr[i] = new Point(x[i], y[i]);
    }
    return ptr;
}

float findMaxThreshold(Line l, float *first, float *sec, int size) {
    float f = 0;
    for (int i = 0; i < size; i++) {
        float tmp = dev(Point(first[i], sec[i]), l);
        // checking the max
        if (tmp > f) {
            f = tmp;
        }
    }
    return f;
}

correlatedFeatures
creatingCorrelationStract(std::string firstName, std::string secName, float *first, float *sec, int size,
                          float corrlation) {
    correlatedFeatures a;
    a.feature1 = firstName;
    a.feature2 = secName;
    a.corrlation = corrlation;
    Line l = linear_reg(points(first, sec, size), size);
    a.lin_reg = l;
    a.threshold = findMaxThreshold(l, first, sec, size);
    return a;

}

void SimpleAnomalyDetector::learnNormal(const TimeSeries &ts) {
    //get floats arrays of the values of ts
    float **fArr = ts.getFloatArrays();

    // first loop
    for (int i = 0; i < ts.getTable().size(); i++) {
        // initializing the corr and the match subject
        int matcher = 0;
        float corrlation = 0.9;
        float *x = fArr[i];

        // for loop for the matcher subject
        for (int j = i + 1; j < ts.getTable().size(); j++) {

            //convert to float****duplicate work
            float *y = fArr[j];

            //checking the corrlation
            float tmp = pearson(x, y, ts.getNumOfValues());
            absFloat(&tmp);
            if (tmp > corrlation) {
                corrlation = tmp;
                matcher = j;
            }
        }

        // creating the struct***????****
        if (corrlation > 0.9) {
            nameToNum[ts.getTable()[i][0]] = i;
            nameToNum[ts.getTable()[matcher][0]] = matcher;
            data.push_back(creatingCorrelationStract
                                   (ts.getName(i), ts.getName(matcher), fArr[i], fArr[matcher],
                                    ts.getNumOfValues(), corrlation));
        }
    }
}

std::vector<correlatedFeatures> SimpleAnomalyDetector::getNormalModel() {
    return data;
}


//std::vector<AnomalyReport> SimpleAnomalyDetector:: detect(const TimeSeries& ts){
//      for(int i=0; i < ts.getNumOfValues() ; i++){
//
//          // the name of the column
//          std:: string name = ts.getTable()[0][i];
//          // finding the struct in
//          int vectorNum = nameToNum[name];
//
//          // run on the lines
//          for(int j = 1; j<ts.getTable()[0].size();j++){
//          data[nameToNum]
//
//          }
//      }
//
//}
std::vector<AnomalyReport> SimpleAnomalyDetector:: detect(const TimeSeries& ts){
    std::vector<AnomalyReport> report;
    float **arr=ts.getFloatArrays();
    for (correlatedFeatures cor: data){
        for (int i = 0; i < ts.getNumOfValues(); ++i) {
            int x = nameToNum[cor.feature1];
            int y = nameToNum[cor.feature2];
            Point p(arr[x][i],arr[y][i]);
            float devision = dev(p,cor.lin_reg);
            if (devision>cor.threshold){
                std::string description = cor.feature1+"-"+cor.feature2;
                report.push_back(AnomalyReport(description,i+1));
            }
        }
    }
}