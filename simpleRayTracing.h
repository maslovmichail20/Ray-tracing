#ifndef ASSIGNMENT_6_ADM_SIMPLERAYTRACING_H
#define ASSIGNMENT_6_ADM_SIMPLERAYTRACING_H

#include <vector>
#include "geometry.h"
#include "DisplayControl.h"
#include "bitmap_image.hpp"
#include "flat.h"

using namespace std;

void simpleRayTracing(
                DisplayControl*,
                vector<vector<double>>&,
                vector<vector<int>>&,
                bitmap_image*
);

vector<flat*> createFlatArray(vector<vector<double>>&, vector<vector<int>>&);

//bool rayIntersectTriangle(
//                vector<double>&,
//                vector<double>&,
//                vector<vector<double>>&,
//                vector<int>&
//);

bool rayIntersectTriangle(
        vector<double>&,
        vector<double>&,
        flat*
);


#endif //ASSIGNMENT_6_ADM_SIMPLERAYTRACING_H
