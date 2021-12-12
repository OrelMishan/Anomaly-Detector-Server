//
// Created by user on 12/12/2021.
//

#ifndef ASS1_HYBRIDANOMALYDETECTOR_H
#define ASS1_HYBRIDANOMALYDETECTOR_H
#include <algorithm>
#include "anomaly_detection_util.h"
#include "AnomalyDetector.h"
#include <map>
#include <vector>

class HybridAnomalyDetector : public SimpleAnomalyDetector{
    virtual void isCorr(const TimeSeries &ts,float **fArr,int i,int matcher, float corrlation ) override;
    correlatedFeatures creatingCorrelationStruct(std::string firstName, std::string secName,
                                                 Point center,float threshold,float corrlation)
};
#endif //ASS1_HYBRIDANOMALYDETECTOR_H
