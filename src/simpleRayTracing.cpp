#include "simpleRayTracing.h"
#include "color.h"
#include "kd-tree.h"
#include "flat.h"
#include "geometry.h"
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
    bmp->set_all_channels(255, 255, 255);

    double x, y, z, dx, dy, dz;
    x = dc->canvas[0][0]; y = dc->canvas[0][1]; z = dc->canvas[1][2];
    dx = dc->dx; dy = dc->dy; dz = dc->dz;

    point* min_p = new point(min[0], min[1], min[2]);
    point* max_p = new point(max[0], max[1], max[2]);
    node* root = new node(0, min_p, max_p);
    build_tree(createFlatArray(vertices, flats), root, 0, 0);

    point* camera = new point(dc->camera[0], dc->camera[1], dc->camera[2]);

    for (int i = 0 ; i < dc->heightPx ; i++) {
        double curX = x; double curY = y;
        for (int j = 0 ; j < dc->widthPx ; j++) {
            curX -= dx; curY += dy;
            point* curPoint = new point(curX, curY, z);

            vector<flat*> res;
            if (ray_in_box(camera, curPoint, root->min, root->max) != -1) {
                res = search_in_tree(camera, curPoint, root);
            }

            vector<double> cp(3, 0);
            for (int i = 0 ; i < 3 ; i++) cp[i] = curPoint->coor[i];

            int numberOfNearest = -1;
            double distance = 10000;

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

vector<flat*> createFlatArray(
        vector<vector<double>> &vertices,
        vector<vector<int>> &flats
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
    }
    return elements;
}
