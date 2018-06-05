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
    width = 2;
    height = 2;

    widthPx = 500;
    heightPx = 500;

    vector<double> empty(3, 0);
    camera = empty;
    camera[0] = 3;
    camera[1] = 1;
    camera[2] = 0;

    vector<vector<double>> empty2(2, empty);
    canvas = empty2;
    canvas[0][0] = 2;
    canvas[0][1] = -1;
    canvas[0][2] = -1;

    canvas[1][0] = 2;
    canvas[1][1] = 1;
    canvas[1][2] = 1;

    light = empty;
    light[0] = 2;
    light[1] = -1;
    light[2] = 1;

    dx = 0;
    dy = width/widthPx;
    dz = height/heightPx;
}

DisplayControl::~DisplayControl() {

}
