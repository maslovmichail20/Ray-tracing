#include "simpleRayTracing.h"
#include <iostream>
#include <cmath>

using namespace std;

void simpleRayTracing(
        DisplayControl* ds,
        vector<vector<double>>& vertexes,
        vector<vector<int>>& figures,
        bitmap_image* bmp
) {
    double x, y, z, dx, dy, dz;
    x = ds->canvas[0][0];
    y = ds->canvas[0][1];
    z = ds->canvas[1][2];

    dx = ds->dx; dy = ds->dy; dz = ds->dz;

    for (int i = 0 ; i < ds->heightPx ; i++) {
        double curX = x; double curY = y;
        for (int j = 0 ; j < ds->widthPx ; j++) {
            vector<double> curPoint(3, 0);
            curX += dx; curY += dy;
            curPoint[0] = curX;
            curPoint[1] = curY;
            curPoint[2] = z;

            for (int k = 0 ; k < figures.size() ; k++) {
                if (rayIntersectTriangle(ds->camera, curPoint, vertexes, figures[k])) {
                    bmp->set_pixel(j, i, 0, 0, 0);
                    break;
                }
            }
        }
        z -= dz;
    }
}


// Möller–Trumbore intersection algorithm
bool rayIntersectTriangle(
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

    vector<double> h = crossProduct(rayVector, edge2);
    double a = dotProduct(edge1, h);
    if (a > -E && a < E) return false;

    double f = 1/a;
    vector<double> s = subtract(rayOrigin, vertex0);
    double u = f * dotProduct(s, h);
    if (u < 0 || u > 1) return false;

    vector<double> q = crossProduct(s, edge1);
    double v = f * dotProduct(rayVector, q);
    if (v < 0 || u + v > 1) return false;

    double t = f * dotProduct(edge2, q);

    return abs(t) > E;
}