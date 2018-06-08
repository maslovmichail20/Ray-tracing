#include "DisplayControl.h"
#include "geometry.h"
#include <cmath>
#include <iostream>

using namespace std;

DisplayControl::DisplayControl(
        vector<double> &min,
        vector<double> &max,
        string resolution
) {
    width = 1;
    height = 1;

    widthPx = 500;
    heightPx = 500;

    vector<double> empty(3, 0);
    camera = empty;
    camera[0] = 0;
    camera[1] = 1001;
    camera[2] = 0;

    vector<vector<double>> empty2(2, empty);
    canvas = empty2;
    canvas[0][0] = -0.5;
    canvas[0][1] = 1000;
    canvas[0][2] = -0.5;

    canvas[1][0] = 0.5;
    canvas[1][1] = 1000;
    canvas[1][2] = 0.5;

    dx = width/widthPx;
    dy = 0;
    dz = height/heightPx;
}

// DisplayControl::~DisplayControl() {
//
// }
