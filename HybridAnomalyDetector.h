//Name: Noam Tzuberi ID:313374837
//Name: Orel Mishan ID:316551092

#ifndef ASS1_HYBRIDANOMALYDETECTOR_H
#define ASS1_HYBRIDANOMALYDETECTOR_H
#include <SimpleAnomalyDetector.h>
#include <minCircle.h>


class HybridAnomalyDetector : public SimpleAnomalyDetector{
    void isCorr(const TimeSeries &ts,float **fArr,int i,int matcher, float corrlation ) override;
    correlatedFeatures creatingCorrelationStruct(std::string firstName, std::string secName,
                                                 Circle c,float corrlation);
    float findDev(Point p,correlatedFeatures cor) override;
public:
    float distance(Point p,Point c);
    HybridAnomalyDetector() = default;
    virtual ~HybridAnomalyDetector() = default;

};
#endif //ASS1_HYBRIDANOMALYDETECTOR_H
