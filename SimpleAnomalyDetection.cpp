#include "AnomalyDetector.h"
#include "SimpleAnomalyDetection.h"

Point **points(float *x, float *y,int size) {
    Point *ptr[size];
    for (int i = 0; i < size; i++) {
        ptr[i] = new Point(x[i], y[i]);
    }
}

correlatedFeatures creatingCorrelationStract(float *first, float* sec,int size, int c) {
    correlatedFeatures a ;
    a.feature1 = first[1];
    a.feature2 = sec[1];
    a.corrlation = c;
    a.lin_reg = linear_reg(points(first, sec,size), size);
    a.threshold;
    return a;

}

void SimpleAnomalyDetector::learnNormal(TimeSeries &ts) {
    //get floats arrays of the values of ts
    float **fArr = ts.getFloatArrays();
    // first loop
    for (int i = 0; i < ts.getTable().size(); i++) {

        // initializing the corr and the match subject
        int matcher = 0, corrlation = -1;
        float *x = fArr[i];

        // for loop for the matcher subject
        for (int j = i+1; j < ts.getTable().size(); j++) {

            //convert to float****duplicate work
            float *y = fArr[j];

            //checking the corralation
            int tmp = pearson(x, y, ts.getNumOfValues());

            if (tmp > corrlation) {
                corrlation = tmp;
                matcher = j;
            }
        }

        // creating the struct
        data.push_back(creatingCorrelationStract
                               (fArr[i], fArr[matcher],ts.getNumOfValues(), corrlation));
    }
};

std::vector<correlatedFeatures> SimpleAnomalyDetector::getNormalModel() {
    return data;
}