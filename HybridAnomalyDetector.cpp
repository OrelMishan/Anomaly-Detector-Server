//Name: Noam Tzuberi ID:313374837
//Name: Orel Mishan ID:316551092

#include <HybridAnomalyDetector.h>
#include <cmath>

void HybridAnomalyDetector::isCorr(const TimeSeries &ts,float **fArr,int i,int matcher, float corrlation ){
    if (corrlation >= 0.9){
         SimpleAnomalyDetector :: isCorr(ts,fArr,i,matcher,corrlation);
    }
    else {
        Point **arrPoints = points(fArr[i], fArr[matcher], ts.getNumOfValues());
        Circle c = findMinCircle(arrPoints,ts.getNumOfValues());
        data.push_back(creatingCorrelationStruct(ts.getName(i), ts.getName(matcher), c,corrlation));
    }

}
float HybridAnomalyDetector:: distance(Point p,Point c) {
    float dis;
    dis = powf(p.x-c.x,2) + powf(p.y-c.y,2);
    return sqrtf(dis);
}

float HybridAnomalyDetector::findDev(Point p,correlatedFeatures cor) {
    if (cor.is_line){
        return SimpleAnomalyDetector::findDev(p,cor);
    }
    return distance(p,cor.c.center);
}
correlatedFeatures HybridAnomalyDetector:: creatingCorrelationStruct(std::string firstName, std::string secName,
                                             Circle c,float corrlation){

    correlatedFeatures a;

    a.is_line=false;
    // add the first feature
    a.feature1 = firstName;
    // add the second feature
    a.feature2 = secName;

    // the correlation
    a.corrlation = corrlation;

    // finding the max threshold
    a.threshold = c.radius * float(1.1);

    a.c = c;

    return a;
}