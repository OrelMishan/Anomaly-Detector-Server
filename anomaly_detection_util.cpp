
#include <cmath>
#include <iostream>
#include "anomaly_detection_util.h"


float expectation(float *x, int size) {
    if( size == 0){
        printf("can't divide by zero");
        return 0;
    }
    float sum = 0;
    for (int i = 0; i < size; i++) {
        sum += x[i];
    }
    return sum / (float) size;
}

float var(float *x, int size) {
    if( size == 0){
        printf("can't divide by zero");
        return 0;
        /// exit???
    }
    float result = 0;
    for (int i = 0; i < size; i++) {
        // each parameter is in pow.
        result += (powf(x[i], 2));
    }
    result /= (float) size;
    float expected = expectation(x, size);
    return result - (pow(expected, (float)2));
}

float cov(float *x, float *y, int size) {
    float multy[size];
    for (int i = 0; i < size; i++) {
        multy[i] = x[i] * y[i];
    }
    return expectation(multy, size) - (expectation(x, size) * expectation(y, size));
}

float pearson(float *x, float *y, int size) {
    float coverage = cov(x, y, size);
    float varX =var(x, size);
    float varY =var(y, size);

    if(varX <= 0 || varY <=0){
        printf("no defined");
        return 0;
    }

    float sqrtX = sqrtf(varX);
    float sqrtY = sqrtf(varY);
    return coverage / (sqrtX * sqrtY);
}

Line linear_reg(Point **points, int size) {
    float x[size], y[size];
    for (int i = 0; i < size; i++) {
        x[i] = points[i]->x;
        y[i] = points[i]->y;
    }
    /// find what happened if the line is parallel
    float varX=var(x, size);
    if( varX == 0) {
        throw "no defined";
    }
    float a = cov(x, y, size) / varX;
    float averageX = expectation(x, size);
    float averageY = expectation(y, size);
    float b = averageY - (a * averageX);
    return {a, b};
}

float dev(Point p,Point** points, int size){
    Line line = linear_reg(points,size);
    return dev(p,line);
}
float dev(Point p,Line l){
    // find the parallel x point on the line.
    float onLine = l.f(p.x);
    return(fabs(p.y-onLine));

}

int main(){
    return 1;
}
