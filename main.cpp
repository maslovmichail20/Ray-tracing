#include <iostream>
#include <vector>
#include "DisplayControl.h"
#include "bitmap_image.hpp"
#include "simpleRayTracing.h"
#include "readObj.h"

using namespace std;


int main() {
    vector<vector<double>> vertices;
    vector<vector<int>> flats;

    vector<double> minCoordinate(3, 0);
    vector<double> maxCoordinate(3, 0);

    readObj("teapot.obj", minCoordinate, maxCoordinate, &vertices, &flats);

    DisplayControl* DC = new DisplayControl(minCoordinate, maxCoordinate, "sd");
    bitmap_image *image = new bitmap_image(DC->widthPx,DC->heightPx);
    image->set_all_channels(255, 255, 255);
    simpleRayTracing(DC, minCoordinate, maxCoordinate, vertices, flats, image);
    image->save_image("output.bmp");

    return 0;
}