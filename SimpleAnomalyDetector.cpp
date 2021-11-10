#include "AnomalyDetector.h"
#include "SimpleAnomalyDetector.h"
#define TRSEHOLD 0.9



float findMaxThreshold(Line l, float *first, float *sec, int size) {
    // the basic threshold at start= 0.
    float f = 0;

    // loop for all the dev in the given data
    for (int i = 0; i < size; i++) {

        //checking the dev fot current values
        float tmp = dev(Point(first[i], sec[i]), l);
        // checking the max between the previous and the current
        if (tmp > f) {
            f = tmp;
        }
    }
    // return little higher than the threshold we got
    return f * (float)1.1 ;
}

Point **points(float *x, float *y, int size) {

    // pointer to points array
    Point **ptr = new Point *[size];

    // create the points
    for (int i = 0; i < size; i++) {
        // put the point in the points array
        ptr[i] = new Point(x[i], y[i]);
    }
    return ptr;
}



correlatedFeatures creatingCorrelationStruct(std::string firstName, std::string secName,
                                             float *first, float *sec, int size, float corrlation) {

    // creating the struct
    correlatedFeatures a;

    // add the first feature
    a.feature1 = firstName;
    // add the second feature
    a.feature2 = secName;

    // the corrlation
    a.corrlation = corrlation;

    // creating the line
    Point **arrPoints=points(first, sec, size);
    a.lin_reg = linear_reg(arrPoints, size);
    for (int i = 0; i < size; ++i) {
        delete []arrPoints[i];
    }
    delete []arrPoints;

    // finding the max threshold
    a.threshold = findMaxThreshold(a.lin_reg, first, sec, size);
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

            // the current corrlation in abs
            absFloat(&tmp);

            // if the tmp more corrltive from the threshold
            if (tmp > corrlation) {
                corrlation = tmp;
                matcher = j;
            }
        }

        // basic corrlation
        if (corrlation > TRSEHOLD) {

            // insert to the map name of the column and it number
            nameToNum[ts.getTable()[i][0]] = i;

            // insert to the map name of the match(corrlative) column and it number
            nameToNum[ts.getTable()[matcher][0]] = matcher;

            // add the struct to the vector of coralletion
            data.push_back(creatingCorrelationStruct
                                   (ts.getName(i), ts.getName(matcher), fArr[i], fArr[matcher],
                                    ts.getNumOfValues(), corrlation));
        }
    }

    // free the arrays
    for (int i = 0; i < ts.getTable().size(); i++) {
        delete[] fArr[i];
    }
    delete fArr;
}

std::vector<correlatedFeatures> SimpleAnomalyDetector::getNormalModel() {
    return data;
}

std::vector<AnomalyReport> SimpleAnomalyDetector::detect(const TimeSeries &ts) {
    // the vector that return the anomaly report
    std::vector<AnomalyReport> report;

    // creating the array of arrays of floats
    float **arr = ts.getFloatArrays();

    // loop for the length of the arrays
    for (int i = 0; i < ts.getNumOfValues(); ++i) {

        // loop for the cf
        for (const correlatedFeatures &cor: data) {

            // the first feature and his column number
            int x = nameToNum[cor.feature1];

            // the second feature and his column number
            int y = nameToNum[cor.feature2];

            // creating the point of the values
            Point p(arr[x][i], arr[y][i]);

            // checking the distance from the line
            float devision = dev(p, cor.lin_reg);

            // if the dis bigger than the threshold report it
            if (devision > cor.threshold) {
                // creating the description
                std::string description = cor.feature1 + "-" + cor.feature2;
                report.push_back(AnomalyReport(description, i + 1));
            }
        }
    }
    return report;
}


