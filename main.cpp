#include <vector>
#include <iostream>
#include <cstring>
#include "./libraries/bitmap_image.hpp"
#include "./src/DisplayControl.h"
#include "./src/simpleRayTracing.h"
#include "./src/readObj.h"

using namespace std;


int main(int argc, char* argv[]) {
    if (argc > 1) {
        vector<vector<double>> vertices;
        vector<vector<int>> flats;
        vector<vector<double>> normals;

        vector<double> minCoordinate(3, 0);
        vector<double> maxCoordinate(3, 0);

        char modelsPath[] = "./models/";
        readObj(
                strcat(modelsPath, argv[1]),
                minCoordinate, maxCoordinate,
                vertices, flats, normals
        );

        int angle = 0;
        if (argv[3]) angle = atoi(argv[3]);

        vector<int> rgb(3, 224);
        if (argv[5]) rgb[0] = atoi(argv[5]);
        if (argv[6]) rgb[1] = atoi(argv[6]);
        if (argv[7]) rgb[2] = atoi(argv[7]);

        DisplayControl *DC = new DisplayControl(
                minCoordinate, maxCoordinate, angle, rgb
        );

        bitmap_image *image = new bitmap_image(DC->widthPx, DC->heightPx);

        simpleRayTracing(
                DC, minCoordinate, maxCoordinate, vertices, flats, normals, image
        );

        char picturesPath[] = "./pictures/";
        strtok(argv[1], "."); strcat(argv[1], ".bmp");
        image->save_image(strcat(picturesPath, argv[1]));
    } else {
        cout << "Invalid arguments" << endl;
    }
    return 0;
}
