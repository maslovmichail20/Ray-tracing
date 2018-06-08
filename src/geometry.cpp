#include "geometry.h"
#include <cmath>

vector<double> add(vector<double>& v1, vector<double>& v2) {
    vector<double> res;
    for (int i = 0 ; i < 3 ; i++) res.push_back(v1[i] + v2[i]);
    return res;
};

vector<double> subtract(vector<double>& v1, vector<double> v2) {
    vector<double> res;
    for (int i = 0 ; i < 3 ; i++) res.push_back(v1[i] - v2[i]);
    return res;
};

double dotProduct(vector<double>& v1, vector<double>& v2) {
    double res = 0;
    for (int i = 0 ; i < 3 ; i++) res += v1[i]*v2[i];
    return res;
};

vector<double> crossProduct(vector<double>& v1, vector<double>& v2) {
    vector<double> res;
    res.push_back(v1[1]*v2[2] - v1[2]*v2[1]);
    res.push_back(v1[2]*v2[0] - v1[0]*v2[2]);
    res.push_back(v1[0]*v2[1] - v1[1]*v2[0]);
    return res;
};

double vectorLength(vector<double>& v) {
    return sqrt(pow(v[0], 2) + pow(v[1], 2) + pow(v[2], 2));
}

vector<double> normalize(vector<double>& v) {
    vector<double> n(3, 0);
    double l = vectorLength(v);
    for (int i = 0 ; i < 3 ; i++) {
        n[i] = v[i] / l;
    }
    return n;
}

vector<double> multiply(vector<double>& v, double m) {
    vector<double> res(3, 0);
    for (int i = 0 ; i < 3 ; i++) {
        res[i] = v[i] * m;
    }
    return res;
}

double cosBetweenVectors(vector<double>& v1, vector<double>& v2) {
    return abs(dotProduct(v1, v2)/(vectorLength(v1) * vectorLength(v2)));
};

void swap_(double* el1, double* el2){
    double swap = *el1;
    *el1 = *el2;
    *el2 = swap;
}

double ray_in_box(point* A, point* B, point* min, point* max){

    double x0 = min -> coor[0];
    double y0 = min -> coor[1];
    double z0 = min -> coor[2];

    double x1 = max -> coor[0];
    double y1 = max -> coor[1];
    double z1 = max -> coor[2];

    double x = A -> coor[0];
    double y = A -> coor[1];
    double z = A -> coor[2];

    point* vector = new point(0,0,0);


    double len = 0;

    for (int i = 0; i < 3; i++){
        vector -> coor[i] = B -> coor[i] - A -> coor[i];
        len += ((vector -> coor[i])*(vector -> coor[i]));
    }

    len = sqrt(len);

    for (int i = 0; i < 3; i++){
        vector -> coor[i] /= len;
    }

    double Tnear = -INT_MAX;
    double Tfar = INT_MAX;

    if (vector -> coor[0] == 0){
        if (x > x1 || x < x0){
            return -1;
        }
    } else {
        Tnear = (x0 - x) / vector -> coor[0];
        Tfar = (x1 - x) / vector -> coor[0];
        if (Tnear > Tfar) swap_(&Tnear, &Tfar);
    }

    if (vector -> coor[1] == 0){
        if (y > y1 || y < y0){
            return -1;
        }
    } else {
        double T1y = (y0 - y) / vector -> coor[1];
        double T2y = (y1 - y) / vector -> coor[1];

        if (T1y > T2y) swap_(&T1y, &T2y);
        if (T1y > Tnear) Tnear = T1y;
        if (T2y < Tfar) Tfar = T2y;
    }

    if (Tnear > Tfar || Tfar < 0) return -1;

    if (vector -> coor[2] == 0){
        if (z > z1 || z < z0){
            return -1;
        }
    } else {
        double T1z = (z0 - z) / vector -> coor[2];
        double T2z = (z1 - z) / vector -> coor[2];

        if (T1z > T2z) swap_(&T1z, &T2z);
        if (T1z > Tnear) Tnear = T1z;
        if (T2z < Tfar) Tfar = T2z;
    }

    if (Tnear > Tfar || Tfar == 0) return -1;

    return Tnear;
}

// Möller–Trumbore intersection algorithm
double rayIntersectTriangle(
        vector<double> &rayOrigin,
        vector<double> &rayVector,
        vector<vector<double>>& vertexes,
        vector<int>& flat
) {
    const double E = 0.0000001;
    vector<double> vertex0 = vertexes[flat[0]];
    vector<double> vertex1 = vertexes[flat[1]];
    vector<double> vertex2 = vertexes[flat[2]];

    vector<double> edge1 = subtract(vertex1, vertex0);
    vector<double> edge2 = subtract(vertex2, vertex0);

    vector<double> dir = subtract(rayVector, rayOrigin);

    vector<double> h = crossProduct(dir, edge2);
    double a = dotProduct(edge1, h);
    if (a > -E && a < E) return -1;

    double f = 1/a;
    vector<double> s = subtract(rayOrigin, vertex0);
    double u = f * dotProduct(s, h);
    if (u < 0 || u > 1) return -1;

    vector<double> q = crossProduct(s, edge1);
    double v = f * dotProduct(dir, q);
    if (v < 0 || u + v > 1) return -1;

    double t = f * dotProduct(edge2, q);
    if (abs(t) > E) {
        return abs(t);
    } else return -1;
}
