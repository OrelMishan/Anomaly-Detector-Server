//
// Created by אוראל משען on 13/10/2021.
//
#include <math.h>

float average(float *x, int size) {
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += x[i];
    }
    return sum / (float) size;
}

float var(float *x, int size) {
    int result = 0;
    for (int i = 0; i < size; i++) {
        result += (powf(x[i], 2));
    }
    result /= (float) size;
    float expected = average(x, size);
    return result - (pow(expected, 2));
}

float cov(float *x, float *y, int size) {
    float multy[size];
    for (int i = 0; i < size; i++) {
        multy[i] = x[i] * y[i];
    }
    return evarage(multy, size) - (evarage(x, size) * evarage(y, size));
}

float pearson(float *x, float *y, int size) {
    float coverage = cov(x, y, size);
    float sqrtX = sqrtf(var(x, size));
    float sqrtY = sqrtf(var(y, size));
    return coverage / (sqrtX * sqrtY);
}

Line linear_reg(Point **points, int size) {
    float x[size], y[size];
    for (int i = 0; i < size; i++) {
        x[i] = points[i].x;
        y[i] = points[i].y;
    }
    float a = cov(x, y, size) / var(x, size);
    float averageX = average(x, size);
    float averageY = average(y, size);
    float b = averageY - (a * averageX);
    return Line(a, b);
}

float dev(Point p,Point** points, int size){
    Line line = linear_reg(points,size);
    return dev(p,line);
}
float dev(Point p,Line l){
}
