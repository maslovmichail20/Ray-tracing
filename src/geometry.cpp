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

double rayIntersectBox(
        vector<double>& rayOrigin,
        vector<double>& rayVector,
        double min[3],
        double max[3])
{
    double x0 = min[0], y0 = min[1], z0 = min[2];
    double x1 = max[0], y1 = max[1], z1 = max[2];

    vector<double> tempV(3, 0);
    for (int i = 0 ; i < 3 ; i++) {
        tempV[i] = rayVector[i] - rayOrigin[i];
    }

    vector<double> normal = normalize(tempV);

    double m = normal[0], n = normal[1], p = normal[2];
    double x = rayOrigin[0], y = rayOrigin[1], z = rayOrigin[2];

    double Tnear = 0, Tfar = 0;

    if (m == 0) {
        if (x > x1 || x < x0) {
            return  0;
        }
    } else {
        Tnear = (x0 - x) / m;
        Tfar = (x1 - x) / m;
        if (Tnear > Tfar) {
            double temp = Tnear;
            Tnear = Tfar;
            Tfar = temp;
        }
    }

    if (n == 0) {
        if (y > y1 || y < y0) {
            return 0;
        }
    } else {
        double T1y = (y0 - y) / n;
        double T2y = (y1 - y) / n;

        if (T1y > T2y) {
            double temp = T1y;
            T1y = T2y;
            T2y = temp;
        }

        if (T1y > Tnear) Tnear = T1y;
        if (T2y < Tfar) Tfar = T2y;
    }

    if (Tnear > Tfar || Tfar < 0) return 0;

    if (p == 0) {
        if (z > z1 || z < z0){
            return 0;
        }
    } else {
        double T1z = (z0 - z) / p;
        double T2z = (z1 - z) / p;

        if (T1z > T2z) {
            double temp = T1z;
            T1z = T2z;
            T2z = temp;
        }

        if (T1z > Tnear) Tnear = T1z;
        if (T2z < Tfar) Tfar = T2z;
    }

    if (Tnear > Tfar || Tfar == 0) return 0;

    return Tnear;
}
