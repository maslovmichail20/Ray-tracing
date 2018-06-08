#include "simpleRayTracing.h"
#include <iostream>
#include <cmath>
#include "kd-tree.h"
#include "limits.h"

using namespace std;

void simpleRayTracing(
        DisplayControl* dc,
        vector<double> &min,
        vector<double> &max,
        vector<vector<double>>& vertexes,
        vector<vector<int>>& figures,
        bitmap_image* bmp
) {
    auto min_ = new point(min[0], min[1], min[2]);
    auto max_ = new point(max[0], max[1], max[2]);
    node* root = new node(0, min_, max_);
    vector<flat*> v = createFlatArray(vertexes, figures);

    int *count = new int;
    *count = 0;
    build_tree(v, root, 0, 0, count);


    cout << "Built " << *count << " nodes" << endl;


    double x, y, z, dx, dy, dz;
    x = dc->canvas[0][0];
    y = dc->canvas[0][1];
    z = dc->canvas[1][2];

    dx = dc->dx; dy = dc->dy; dz = dc->dz;
    auto camera = new point(dc->camera[0], dc->camera[1], dc->camera[2]);

    for (int i = 0 ; i < dc->heightPx ; i++) {
        double curX = x; double curY = y;
        for (int j = 0 ; j < dc->widthPx ; j++) {
            curX += dx; curY += dy;
            auto curP = new point(curX, curY, z);
            vector<flat*> resFlats;

            if(ray_in_box(camera, curP, root -> min, root -> max)!= INT_MAX){
               resFlats = search_in_tree(camera, curP, root);
               //cout << resFlats.size() << endl;
            }

            vector<double> curPoint(3, 0);
            curPoint[0] = curX;
            curPoint[1] = curY;
            curPoint[2] = z;

            for (int k = 0 ; k < resFlats.size() ; k++) {
                if (rayIntersectTriangle(dc->camera, curPoint, resFlats[k])) {
                    //cout << "Intersection" << endl;
                    bmp->set_pixel(j, i, 0, 0, 0);
                    break;
                }
            }

//            vector<double> curPoint(3, 0);
//            curX += dx; curY += dy;
//            curPoint[0] = curX;
//            curPoint[1] = curY;
//            curPoint[2] = z;

//            for (int k = 0 ; k < figures.size() ; k++) {
//                if (rayIntersectTriangle(dc->camera, curPoint, vertexes, figures[k])) {
//                    bmp->set_pixel(j, i, 0, 0, 0);
//                    break;
//                }
//            }
        }
        z -= dz;
    }
}

vector<flat*> createFlatArray(vector<vector<double>> &vertices,
                              vector<vector<int>> &flats)
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
                          vertices[flats[i][2]][2])
        );
    }
    return elements;
}


bool rayIntersectTriangle(
        vector<double> &rayOrigin,
        vector<double> &rayVector,
        flat* triangle
) {
    const double E = 0.0000001;
    vector<double> vertex0(3, 0);
    vector<double> vertex1(3, 0);
    vector<double> vertex2(3, 0);

    for (int i = 0 ; i < 3 ; i++) {
        vertex0[i] = triangle->p1->coor[i];
        vertex1[i] = triangle->p2->coor[i];
        vertex2[i] = triangle->p3->coor[i];
    }

    vector<double> edge1 = subtract(vertex1, vertex0);
    vector<double> edge2 = subtract(vertex2, vertex0);
    vector<double> dir = subtract(rayVector, rayOrigin);

    vector<double> h = crossProduct(dir, edge2);
    double a = dotProduct(edge1, h);
    if (a > -E && a < E) return false;

    double f = 1/a;
    vector<double> s = subtract(rayOrigin, vertex0);
    double u = f * dotProduct(s, h);
    if (u < 0 || u > 1) return false;

    vector<double> q = crossProduct(s, edge1);
    double v = f * dotProduct(dir, q);
    if (v < 0 || u + v > 1) return false;

    double t = f * dotProduct(edge2, q);

    return abs(t) > E;
}
