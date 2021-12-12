//
// Created by user on 12/12/2021.
//

#ifndef ASS1_MINCIRCLE_H
#define ASS1_MINCIRCLE_H

#include <iostream>
#include <vector>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include "anomaly_detection_util.h"

using namespace std;


// ------------ DO NOT CHANGE -----------

class Circle{
public:
    Point center;
    float radius;
    Circle(Point c,float r):center(c),radius(r){}
};
// --------------------------------------

Circle findMinCircle(Point** points,size_t size);

// you can add here additional methods



#endif //ASS1_MINCIRCLE_H
