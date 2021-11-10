//
// Created by user on 03/11/2021.
//

#ifndef ASS1_SIMPLEANOMALYDETECTOR_H
#define ASS1_SIMPLEANOMALYDETECTOR_H

#include "anomaly_detection_util.h"
#include "AnomalyDetector.h"
#include <map>
#include <vector>

struct correlatedFeatures {
    std::string feature1, feature2; // names of the correlated features
    float corrlation;
    Line lin_reg;
    float threshold;
};

class SimpleAnomalyDetector : public TimeSeriesAnomalyDetector {
    std::vector<correlatedFeatures> data;
    std::map<std::string, int> nameToNum;
public:
    SimpleAnomalyDetector() = default;

    virtual ~SimpleAnomalyDetector() = default;

    virtual void learnNormal(const TimeSeries &ts);

    virtual std::vector<AnomalyReport> detect(const TimeSeries &ts);

    std::vector<correlatedFeatures> getNormalModel();
};

#endif //ASS1_SIMPLEANOMALYDETECTOR_H
