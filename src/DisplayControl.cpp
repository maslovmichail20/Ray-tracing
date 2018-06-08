#include "DisplayControl.h"
#include "geometry.h"
#include <cmath>
#include <iostream>

using namespace std;

DisplayControl::DisplayControl(
        vector<double> &min,
        vector<double> &max
) {
    width = 1;
    height = 1;

    widthPx = 300;
    heightPx = 300;

    vector<double> empty(3, 0);
    camera = empty;
    camera[0] = 1001;
    camera[1] = 0;
    camera[2] = 0;

    vector<vector<double>> empty2(2, empty);
    canvas = empty2;
    canvas[0][0] = 1000;
    canvas[0][1] = -0.5;
    canvas[0][2] = -0.5;

    canvas[1][0] = 1000;
    canvas[1][1] = 0.5;
    canvas[1][2] = 0.5;

    light = canvas[0];

    dx = 0;
    dy = width/widthPx;
    dz = height/heightPx;
}

// DisplayControl::~DisplayControl() {
//
// }
