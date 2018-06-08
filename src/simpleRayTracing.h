#ifndef ASSIGNMENT_6_ADM_SIMPLERAYTRACING_H
#define ASSIGNMENT_6_ADM_SIMPLERAYTRACING_H

#include <vector>
#include "DisplayControl.h"
#include "flat.h"
#include "../libraries/bitmap_image.hpp"

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

vector<flat*> createFlatArray(vector<vector<double>>&, vector<vector<int>>&);


#endif //ASSIGNMENT_6_ADM_SIMPLERAYTRACING_H
