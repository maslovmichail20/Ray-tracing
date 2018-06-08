#ifndef ASSIGNMENT_6_ADM_SIMPLERAYTRACING_H
#define ASSIGNMENT_6_ADM_SIMPLERAYTRACING_H

#include <vector>
#include "geometry.h"
#include "DisplayControl.h"
#include "../libraries/bitmap_image.hpp"
#include "flat.h"

using namespace std;

void simpleRayTracing(
                DisplayControl*,
                vector<double>&,
                vector<double>&,
                vector<vector<double>>&,
                vector<vector<int>>&,
                vector<vector<double>>&,
                bitmap_image*
);

vector<flat*> createFlatArray(vector<vector<double>>&, vector<vector<int>>&, vector<vector<double>>&);

double rayIntersectTriangle(
        vector<double> &rayOrigin,
        vector<double> &rayVector,
        vector<vector<double>>& vertexes,
        vector<int>& flat
);


#endif //ASSIGNMENT_6_ADM_SIMPLERAYTRACING_H
