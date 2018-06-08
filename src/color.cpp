#include "color.h"
#include "geometry.h"

using namespace std;

int getColor(
        vector<double> &camera,
        vector<double> &point,
        vector<double> &light,
        double distance,
        vector<double> &normal
) {
    vector<double> direction(3, 0);
    for (int i = 0 ; i < 3 ; i++) {
        direction[i] = point[i] - camera[i];
    }

    vector<double> normDir = normalize(direction);
    vector<double> d = multiply(normDir, distance);

    vector<double> target(3, 0);
    for (int i = 0 ; i < 3 ; i++) {
        target[i] = camera[i] + d[i];
    }

    vector<double> lightV(3, 0);
    for (int i = 0 ; i < 3 ; i++) {
        lightV[i] = light[i] - target[i];
    }

    double angleCos = cosBetweenVectors(normal, lightV);

    return int(244 - 190*angleCos);
}