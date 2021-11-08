//
// Created by user on 03/11/2021.
//

#ifndef ASS1_SIMPLEANOMALYDETECTION_H
#define ASS1_SIMPLEANOMALYDETECTION_H

#include "anomaly_detection_util.h"

struct correlatedFeatures{
    std::string feature1,feature2; // names of the correlated features
    float corrlation;
    Line lin_reg;
    float threshold;
};
class SimpleAnomalyDetector:public TimeSeriesAnomalyDetector{
    std::vector<correlatedFeatures> data;
public:
    SimpleAnomalyDetector();
    virtual ~SimpleAnomalyDetector();
    virtual std::vector<AnomalyReport> detect(const TimeSeries& ts);
    std::vector<correlatedFeatures> getNormalModel();

    void learnNormal(TimeSeries &ts);
};

#endif //ASS1_SIMPLEANOMALYDETECTION_H
