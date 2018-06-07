#ifndef ASSIGNMENT_6_ADM_SIMPLERAYTRACING_H
#define ASSIGNMENT_6_ADM_SIMPLERAYTRACING_H

#include <vector>
#include "geometry.h"
#include "DisplayControl.h"
#include "../libraries/bitmap_image.hpp"
#include "KD_tree.h"


using namespace std;

void simpleRayTracing(
                DisplayControl*,
                vector<vector<double>>&,
                vector<vector<int>>&,
                vector<vector<double>>&,
                KD_tree*,
                bitmap_image*
);

double rayIntersectTriangle(
                vector<double>&,
                vector<double>&,
                vector<vector<double>>&,
                vector<int>&
);


#endif //ASSIGNMENT_6_ADM_SIMPLERAYTRACING_H
