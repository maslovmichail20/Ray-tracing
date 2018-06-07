#include <iostream>
#include <vector>
#include "src/DisplayControl.h"
#include "libraries/bitmap_image.hpp"
#include "src/simpleRayTracing.h"
#include "src/readObj.h"
#include "src/KD_tree.h"

using namespace std;


int main() {
    vector<vector<double>> vertices;
    vector<vector<int>> flats;
    vector<vector<double>> normals;

    vector<double> minCoordinate(3, 0);
    vector<double> maxCoordinate(3, 0);

    readObj("./models/cow.obj", minCoordinate, maxCoordinate, &vertices, &flats, &normals);

    vector<Box*> allBoxes = createBoxesArray(vertices, flats);
    KD_tree* kd = new KD_tree(minCoordinate.data(), maxCoordinate.data(), allBoxes);
    kd->buildTree(kd->root);
    kd->show(kd->root);
    DisplayControl* DC = new DisplayControl(minCoordinate, maxCoordinate, "sd");
    bitmap_image *image = new bitmap_image(DC->widthPx,DC->heightPx);
    image->set_all_channels(255, 255, 255);
    simpleRayTracing(DC, vertices, flats, normals, kd, image);
    image->save_image("./pictures/output.bmp");

    return 0;
}