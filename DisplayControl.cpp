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

    widthPx = 128;
    heightPx = 128;

    vector<double> empty(3, 0);
    camera = empty;
    camera[0] = 5;
    camera[1] = 0;
    camera[2] = 0;

    vector<vector<double>> empty2(2, empty);
    canvas = empty2;
    canvas[0][0] = 4;
    canvas[0][1] = -0.5;
    canvas[0][2] = -0.5;

    canvas[1][0] = 4;
    canvas[1][1] = 0.5;
    canvas[1][2] = 0.5;

    dx = 0;
    dy = width/widthPx;
    dz = height/heightPx;
}

// DisplayControl::~DisplayControl() {
//
// }
