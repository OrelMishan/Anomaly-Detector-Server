#include "AnomalyDetector.h"
#include "SimpleAnomalyDetection.h"

float* phraseToFloat(std::vector<std::string> vec){
    float* arr = new float[vec.size()-1];
    for(int i=1;i<vec.size();i++){
        arr[i-1]=std::stof(vec[1]);
    }
    return arr;
}
Point** points(float* x,float* y){
    Point *ptr[sizeof(x)];
    for(int i = 0 ; i < sizeof (x);i++){
    ptr[i]=new Point(x[i],y[i]);
    }
}

correlatedFeatures creatingCorrelationStract(std::vector<std::string> first, std::vector<std::string> sec,int c){
        correlatedFeatures a = new correlatedFeatures();
        a.feature1 = first[1];
        a.feature2 = sec[1];
        a.corrlation=c;
        a.lin_reg= linear_reg(points(phraseToFloat(first),phraseToFloat(sec)),sizeof (first));
        a.threshold;
        return a;

    }

void SimpleAnomalyDetector::learnNormal(TimeSeries &ts)  {
    for (int i =0;i < ts.getTable().size() ; i++){
        int matcher,corrlation=0;
        float* x= phraseToFloat(ts.getTable()[i]);
        for(int j=i; j < ts.getTable().size(); j++){
            float* y=phraseToFloat(ts.getTable()[j]);
            int tmp= pearson(x,y,sizeof (x));
            if(tmp > corrlation){
                corrlation=tmp;
                matcher = j;
            }
        }
        data.push_back(creatingCorrelationStract
        (ts.getTable()[i],ts.getTable()[matcher],corrlation));
    }
};

std::vector<correlatedFeatures> SimpleAnomalyDetector::getNormalModel() {
    return data;
}