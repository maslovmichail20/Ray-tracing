#ifndef ASSIGNMENT_6_ADM_GEOMETRY_H
#define ASSIGNMENT_6_ADM_GEOMETRY_H


#include <vector>
#include <climits>
#include "flat.h"
#include <cmath>
#include "sort.h"

using namespace std;

vector<double> add(vector<double>&, vector<double>&);

vector<double> subtract(vector<double>&, vector<double>);

double dotProduct(vector<double>&, vector<double>&);

vector<double> crossProduct(vector<double>&, vector<double>&);

void swap_(double*, double*);

double ray_in_box(point*, point*, point*, point*);

double vectorLength(vector<double>&);

vector<double> normalize(vector<double>&);

vector<double> multiply(vector<double>&, double);

double cosBetweenVectors(vector<double>&, vector<double>&);

double rayIntersectTriangle(
        vector<double> &rayOrigin,
        vector<double> &rayVector,
        vector<vector<double>>& vertexes,
        vector<int>& flat
);


#endif //ASSIGNMENT_6_ADM_GEOMETRY_H
