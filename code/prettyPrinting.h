#ifndef PRETTYPRINT
#define PRETTYPRINT

#include<Interval.h>
#include<cstdio>
#include <iostream>
#include <fstream>
using namespace std;
#include<vector>

typedef struct BoundingBox {
    INTERVAL interTime;
    INTERVAL interVals;

    BoundingBox () {}
    BoundingBox(INTERVAL utT, INTERVAL utV) : interTime(utT), interVals(utV) {}
} BoundingBox;

void printBoundingBoxesToFile(string nomFichier, vector<BoundingBox> boxes);

#endif