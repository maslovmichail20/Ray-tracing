#include "geometry.h"

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