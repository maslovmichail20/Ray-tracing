#ifndef ASSIGNMENT_6_ADM_CREATECANVAS_H
#define ASSIGNMENT_6_ADM_CREATECANVAS_H

#include <vector>
#include <string>

using namespace std;

class DisplayControl {
public:
    DisplayControl(vector<double>&, vector<double>&, string);
    vector<double> camera;
    vector<double> light;
    vector<vector<double>> canvas;
    unsigned int widthPx;
    unsigned int heightPx;
    double width;
    double height;
    double dx;
    double dy;
    double dz;
    ~DisplayControl();
};


#endif //ASSIGNMENT_6_ADM_CREATECANVAS_H
