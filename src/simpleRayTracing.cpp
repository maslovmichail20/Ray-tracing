#include "simpleRayTracing.h"
#include "color.h"
#include "kd-tree.h"
#include "flat.h"
#include <vector>
#include <iostream>
#include <cmath>

using namespace std;

void simpleRayTracing(
        DisplayControl* dc,
        vector<double>& min,
        vector<double>& max,
        vector<vector<double>>& vertices,
        vector<vector<int>>& flats,
        vector<vector<double>>& normals,
        bitmap_image* bmp
) {
    double x, y, z, dx, dy, dz;
    x = dc->canvas[0][0];
    y = dc->canvas[0][1];
    z = dc->canvas[1][2];
    dx = dc->dx; dy = dc->dy; dz = dc->dz;

    point* min_p = new point(min[0], min[1], min[2]);
    point* max_p = new point(max[0], max[1], max[2]);
    node* root = new node(0, min_p, max_p);
    build_tree(createFlatArray(vertices, flats, normals), root, 0, 0);

    point* camera = new point(dc->camera[0], dc->camera[1], dc->camera[2]);

    for (int i = 0 ; i < dc->heightPx ; i++) {
        double curX = x; double curY = y;
        for (int j = 0 ; j < dc->widthPx ; j++) {
            curX += dx; curY += dy;
            point* curPoint = new point(curX, curY, z);

            vector<flat*> res;
            if (ray_in_box(camera, curPoint, root->min, root->max) != -1) {
                res = search_in_tree(camera, curPoint, root);
            }

            int numberOfNearest = -1;
            double distance = 10000;

            vector<double> cp(3, 0);
            for (int i = 0 ; i < 3 ; i++) cp[i] = curPoint->coor[i];

            for (int k = 0 ; k < res.size() ; k++) {
                double curDistance = rayIntersectTriangle(
                        dc->camera,
                        cp,
                        vertices,
                        flats[res[k]->flatIndex]);
                if (curDistance != -1 && curDistance < distance) {
                    distance = curDistance;
                    numberOfNearest = res[k]->flatIndex;
                }
            }

            if (numberOfNearest > -1 && distance != 10000) {
                int rgb = getColor(
                        dc->camera,
                        cp,
                        dc->light,
                        distance,
                        normals[numberOfNearest]
                );
                bmp->set_pixel(j, i, 0, 0, rgb);
            }
        }
        z -= dz;
    }
}

vector<flat*> createFlatArray(vector<vector<double>> &vertices,
                              vector<vector<int>> &flats,
                              vector<vector<double>> &normals
)
{
    vector<flat*> elements(flats.size(), nullptr);
    for (int i = 0 ; i < flats.size() ; i++) {
        elements[i] = new flat(
                new point(vertices[flats[i][0]][0],
                          vertices[flats[i][0]][1],
                          vertices[flats[i][0]][2]),
                new point(vertices[flats[i][1]][0],
                          vertices[flats[i][1]][1],
                          vertices[flats[i][1]][2]),
                new point(vertices[flats[i][2]][0],
                          vertices[flats[i][2]][1],
                          vertices[flats[i][2]][2]),
                i
        );
        vector<double> a = vertices[flats[i][0]];
        vector<double> b = vertices[flats[i][1]];
        vector<double> c = vertices[flats[i][2]];

        normals[i][0] = (b[1] - a[1])*(c[2] - a[2]) - (b[2] - a[2])*(c[1] - a[1]);
        normals[i][1] = (c[0] - a[0])*(b[2] - a[2]) - (b[0] - a[0])*(c[2] - a[2]);
        normals[i][2] = (b[0] - a[0])*(c[1] - a[1]) - (c[0] - a[0])*(b[1] - a[1]);
    }
    return elements;
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