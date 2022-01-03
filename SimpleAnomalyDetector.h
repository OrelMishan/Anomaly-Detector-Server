//Name: Noam Tzuberi ID:313374837
//Name: Orel Mishan ID:316551092

#ifndef ASS1_SIMPLEANOMALYDETECTOR_H
#define ASS1_SIMPLEANOMALYDETECTOR_H
#include <algorithm>
#include "anomaly_detection_util.h"
#include "AnomalyDetector.h"
#include "minCircle.h"
#include <map>
#include <vector>

struct correlatedFeatures {
    bool is_line;
    std::string feature1, feature2; // names of the correlated features
    float corrlation;
    Line lin_reg;
    float threshold;
    Circle c =Circle (Point(0,0),0);
};

class SimpleAnomalyDetector : public TimeSeriesAnomalyDetector {
protected:
    float lineTreshold =0.9;
    std::vector<correlatedFeatures> data;
    std::map<std::string, int> nameToNum;
    virtual void isCorr(const timeseries &ts, float **fArr, int i, int matcher, float corrlation);
    Line lin_reg(float *first, float *sec, int size);
    virtual float findDev(Point p,correlatedFeatures cor);
    Point **points(float *x, float *y, int size);

public:
    SimpleAnomalyDetector() = default;

    virtual ~SimpleAnomalyDetector() = default;

    virtual void learnNormal(const timeseries &ts);

    virtual std::vector<AnomalyReport> detect(const timeseries &ts);
    void setThreshold(float currentCorr);
    float getThreshold() const;
    std::vector<correlatedFeatures> getNormalModel();



};

#endif //ASS1_SIMPLEANOMALYDETECTOR_H
