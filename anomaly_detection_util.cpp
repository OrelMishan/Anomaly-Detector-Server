#include <cmath>
#include <iostream>
#include "anomaly_detection_util.h"

/**
 * @param x is pointer to array of floats that represents a Sample.
 * @param size of the x array.
 * @return the Expected value of the sample.
 */
float expectation(float *x, int size) {
    if (size == 0) {
        throw std ::invalid_argument("can't divide by zero");
    }
    float sum = 0;
    for (int i = 0; i < size; i++) {
        sum += x[i];
    }
    return sum / (float) size;
}

/**
 * @param x is pointer to array of floats that represents a Sample.
 * @param size of the x array.
 * @return the variance of the sample.
 */
float var(float *x, int size) {
    if (size == 0) {
        throw std ::invalid_argument("can't divide by zero");
    }
    float result = 0;
    for (int i = 0; i < size; i++) {
        // each parameter is in pow.
        result += (powf(x[i], 2));
    }
    result /= (float) size;

    float expected = expectation(x, size);
    return result - (pow(expected, (float) 2));
}

/**
 * @param x is a pointer to the first sample.
 * @param y is a pointer to the second sample.
 * @param size of the samples.
 * @return the covariance between the samples.
 */
float cov(float *x, float *y, int size) {
    float multy[size];
    for (int i = 0; i < size; i++) {
        multy[i] = x[i] * y[i];
    }
    return expectation(multy, size) - (expectation(x, size) * expectation(y, size));
}

/**
 * @param x is a pointer to the first sample.
 * @param y is a pointer to the second sample.
 * @param size of the samples.
 * @return the pearson of the samples.
 */
float pearson(float *x, float *y, int size) {
    float coverage = cov(x, y, size);
    float varX = var(x, size);
    float varY = var(y, size);
    if (varX <= 0 || varY <= 0) {
        throw "no defined";
    }
    float sqrtX = sqrtf(varX);
    float sqrtY = sqrtf(varY);
    return coverage / (sqrtX * sqrtY);
}

/**
 *
 * @param points is pointer to array of pints that represent the x and y values of the sample.
 * @param size of the array.
 * @return the linear regression between x and y values.
 */
Line linear_reg(Point **points, int size) {
    float x[size], y[size];
    for (int i = 0; i < size; i++) {
        x[i] = points[i]->x;
        y[i] = points[i]->y;
    }
    float varX = var(x, size);
    if (varX == 0) {
        throw "no defined";
    }
    float a = cov(x, y, size) / varX;
    float averageX = expectation(x, size);
    float averageY = expectation(y, size);
    float b = averageY - (a * averageX);
    return Line(a, b);
}

/**
 * @param p is the point that need to find her deviation.
 * @param points represent the samples.
 * @param size of the points array.
 * @return the deviation between point p and the line equation of the points.
 */
float dev(Point p, Point **points, int size) {
    Line line = linear_reg(points, size);
    return dev(p, line);
}

/**
 * @param p is the point that need to find her deviation.
 * @param l is the linear regression.
 * @return the deviation between point p and the line.
 */
float dev(Point p, Line l) {
    // find the parallel x point on the line.
    float onLine = l.f(p.x);
    return (fabs(p.y - onLine));

}