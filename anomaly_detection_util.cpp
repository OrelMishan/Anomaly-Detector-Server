
#include <math.h>
#include <anomaly_detection_util.h>


float expectation(float *x, int size) {
    if( size == 0){
        cout << "can't divide by zero";
        retunr 0;
    }
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += x[i];
    }
    return sum / (float) size;
}

float var(float *x, int size) {
    if( size == 0){
        cout << "can't divide by zero";
        retunr 0;
        /// exit???
    }
    int result = 0;
    for (int i = 0; i < size; i++) {
        // each parameter is in pow.
        result += (powf(x[i], 2));
    }
    result /= (float) size;
    float expected = expectation(x, size);
    return result - (pow(expected, 2));
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
    /// find what happened if the line is parallel
    float a = cov(x, y, size) / var(x, size);
    float averageX = expectation(x, size);
    float averageY = expectation(y, size);
    float b = averageY - (a * averageX);
    return Line(a, b);
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
