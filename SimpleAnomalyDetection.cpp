#include <map>
#include "AnomalyDetector.h"
#include "SimpleAnomalyDetection.h"
#include "math.h"

float findMaxThreshold(Line line, float *pDouble, float *pDouble1, int size);

Point **points(float *x, float *y, int size) {
    Point *ptr[size];
    for (int i = 0; i < size; i++) {
        ptr[i] = new Point(x[i], y[i]);
    }
}

float findMaxThreshold(Line l,float *first, float* sec,int size){
    float f=0;
    for(int i =0; i < size; i++){
        float  tmp=dev(Point(first[i],sec[i]),l);
        // checking the max
        if(tmp > f){
            f = tmp;
        }
    }
    return f;
}

correlatedFeatures creatingCorrelationStract(float *first, float* sec,int size, int corrlation) {
    correlatedFeatures a;
    a.feature1 = first[1];
    a.feature2 = sec[1];
    a.corrlation = corrlation;
    Line l=linear_reg(points(first, sec,size), size);
    a.lin_reg = l;
    a.threshold = findMaxThreshold(l,first,sec,size);
    return a;

}

void SimpleAnomalyDetector::learnNormal(TimeSeries &ts) {
    //get floats arrays of the values of ts
    float **fArr = ts.getFloatArrays();
    int counter = 0;

    // first loop
    for (int i = 0; i < ts.getTable().size(); i++) {
        // initializing the corr and the match subject
        int matcher = 0;
        float corrlation = 0.2;
        float *x = fArr[i];

        // for loop for the matcher subject
        for (int j = i + 1; j < ts.getTable().size(); j++) {

            //convert to float****duplicate work
            float *y = fArr[j];

            //checking the corralation
            float tmp = pearson(x, y, ts.getNumOfValues());

            if (tmp > corrlation && tmp < 1 * corrlation) {
                corrlation = tmp;
                matcher = j;
            }
        }

        // creating the struct***????****
        if (corrlation != 0.2) {
            nameToNum[ts.getTable()[i][0]] = counter;
            counter++;
            data.push_back(creatingCorrelationStract
                                   (fArr[i], fArr[matcher], ts.getNumOfValues(), corrlation));
        }
    }
}

std::vector<correlatedFeatures> SimpleAnomalyDetector::getNormalModel() {
    return data;
}
/**
//
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
*/
//}
