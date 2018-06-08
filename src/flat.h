#ifndef ASSIGNMENT_6_ADM_FLAT_H
#define ASSIGNMENT_6_ADM_FLAT_H

#include <iostream>

double comparator(double, double, double, int);

struct point{
  double *coor = new double[3];
  point(){
    coor[0] = 0;
    coor[1] = 0;
    coor[2] = 0;
  }
  point(double x, double y, double z){
    coor[0] = x;
    coor[1] = y;
    coor[2] = z;
  }
  void print(){
    std::cout << " x: " << coor[0];
    std::cout << " y: " << coor[1];
    std::cout << " z: " << coor[2] << std::endl;
  }
};

struct flat{
  point* p1;
  point* p2;
  point* p3;
  point* min_p;
  point* max_p;
  int flatIndex;
  flat(point* _p1, point* _p2, point* _p3, int j){
    min_p = new point();
    max_p = new point();
    p1 = _p1;
    p2 = _p2;
    p3 = _p3;
    for (int i = 0; i < 3; i++){
      min_p -> coor[i] = comparator(_p1 -> coor[i], _p2 -> coor[i], _p3 -> coor[i], 0);
      max_p -> coor[i] = comparator(_p1 -> coor[i], _p2 -> coor[i], _p3 -> coor[i], 1);
    }
    flatIndex = j;
  }
};

#endif //ASSIGNMENT_6_ADM_FLAT_H
