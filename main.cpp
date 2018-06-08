#include <iostream>
#include <vector>
#include "./src/DisplayControl.h"
#include "./libraries/bitmap_image.hpp"
#include "./src/simpleRayTracing.h"
#include "./src/readObj.h"

using namespace std;


int main() {
    vector<vector<double>> vertices;
    vector<vector<int>> flats;
    vector<vector<double>> normals;

    vector<double> minCoordinate(3, 0);
    vector<double> maxCoordinate(3, 0);

    readObj("./models/cow.obj", minCoordinate, maxCoordinate, &vertices, &flats, &normals);

    DisplayControl* DC = new DisplayControl(minCoordinate, maxCoordinate);
    bitmap_image *image = new bitmap_image(DC->widthPx,DC->heightPx);
    image->set_all_channels(255, 255, 255);

    simpleRayTracing(DC, minCoordinate, maxCoordinate, vertices, flats, normals, image);

    image->save_image("./pictures/output.bmp");

    return 0;
}
