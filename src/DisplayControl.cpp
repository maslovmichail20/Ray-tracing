#include "DisplayControl.h"
#include "geometry.h"
#include <cmath>
#include <iostream>
#define PI 3.14159265

using namespace std;

DisplayControl::DisplayControl(
        vector<double> &min,
        vector<double> &max,
        int angle_in_deg
) {
    double angle = (PI*angle_in_deg)/180;
    double R = 0;

    for (int i = 0; i < 3; i++){
        if (abs(min[i]) > R) R = abs(min[i]);
        if (abs(max[i]) > R) R = abs(max[i]);
    }

    R*=3;
    width = 1;
    height = 1;

    widthPx = 500;
    heightPx = 500;

    vector<double> empty(3, 0);
    camera = empty;
    camera[0] = R*cos(angle);
    camera[1] = R*sin(angle);
    camera[2] = 0;

    vector<vector<double>> empty2(2, empty);
    canvas = empty2;
    canvas[0][0] = camera[0] + (width / 2)*sin(angle) - cos(angle);
    canvas[0][1] = camera[1] - (width / 2)*cos(angle) - sin(angle);
    canvas[0][2] = -0.5;

    canvas[1][0] = camera[0] - (width / 2)*sin(angle) - cos(angle);
    canvas[1][1] = camera[1] + (width / 2)*cos(angle) - sin(angle);
    canvas[1][2] = 0.5;

    light = canvas[0];

    dx = (width/heightPx)*sin(angle);
    dy = (width/widthPx)*cos(angle);
    dz = height/heightPx;
}

// DisplayControl::~DisplayControl() {
//
// }
