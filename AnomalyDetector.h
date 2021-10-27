//
// Created by user on 27/10/2021.
//

#ifndef ASS1_ANOMALYDETECTOR_H
#define ASS1_ANOMALYDETECTOR_H
class TimeSeries{ /*...*/};
class AnomalyReport{
public:
    const string description;
    const long timeStep;
    AnomalyReport(string description, long timeStep) :
            description(description),timeStep(timeStep){}
};
class TimeSeriesAnomalyDetector {
public:
    virtual void learnNormal(const TimeSeries& ts)=0;
    virtual vector<AnomalyReport> detect(const TimeSeries& ts)=0;
    virtual ~TimeSeriesAnomalyDetector(){}
};

#endif //ASS1_ANOMALYDETECTOR_H
