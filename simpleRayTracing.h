#ifndef ASSIGNMENT_6_ADM_SIMPLERAYTRACING_H
#define ASSIGNMENT_6_ADM_SIMPLERAYTRACING_H

#include <vector>
#include "geometry.h"
#include "DisplayControl.h"
#include "bitmap_image.hpp"

using namespace std;

void simpleRayTracing(
                DisplayControl*,
                vector<vector<double>>&,
                vector<vector<int>>&,
                bitmap_image*
);

bool rayIntersectTriangle(
                vector<double>&,
                vector<double>&,
                vector<vector<double>>&,
                vector<int>&
);


#endif //ASSIGNMENT_6_ADM_SIMPLERAYTRACING_H
