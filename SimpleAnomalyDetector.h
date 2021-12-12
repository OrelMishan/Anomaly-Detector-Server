//Name: Noam Tzuberi ID:313374837
//Name: Orel Mishan ID:316551092

#ifndef ASS1_SIMPLEANOMALYDETECTOR_H
#define ASS1_SIMPLEANOMALYDETECTOR_H
#include <algorithm>
#include "anomaly_detection_util.h"
#include "AnomalyDetector.h"
#include <map>
#include <vector>

struct correlatedFeatures {
    bool is_line;
    std::string feature1, feature2; // names of the correlated features
    float corrlation;
    Line lin_reg;
    float threshold;
    Point center = Point (0,0);
};

class SimpleAnomalyDetector : public TimeSeriesAnomalyDetector {
protected:
    std::vector<correlatedFeatures> data;
    std::map<std::string, int> nameToNum;
    virtual void isCorr(const TimeSeries &ts,float **fArr,int i,int matcher, float corrlation );
    Line lin_reg(float *first, float *sec, int size);

public:
    SimpleAnomalyDetector() = default;

    virtual ~SimpleAnomalyDetector() = default;

    virtual void learnNormal(const TimeSeries &ts);

    virtual std::vector<AnomalyReport> detect(const TimeSeries &ts);

    std::vector<correlatedFeatures> getNormalModel();



};

#endif //ASS1_SIMPLEANOMALYDETECTOR_H
