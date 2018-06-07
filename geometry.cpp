#include "geometry.h"

vector<double> add(vector<double>& v1, vector<double>& v2) {
    vector<double> res;
    for (int i = 0 ; i < 3 ; i++) res.push_back(v1[i] + v2[i]);
    return res;
};

vector<double> subtract(vector<double>& v1, vector<double> v2) {
    vector<double> res;
    for (int i = 0 ; i < 3 ; i++) res.push_back(v1[i] - v2[i]);
    return res;
};

double dotProduct(vector<double>& v1, vector<double>& v2) {
    double res = 0;
    for (int i = 0 ; i < 3 ; i++) res += v1[i]*v2[i];
    return res;
};

vector<double> crossProduct(vector<double>& v1, vector<double>& v2) {
    vector<double> res;
    res.push_back(v1[1]*v2[2] - v1[2]*v2[1]);
    res.push_back(v1[2]*v2[0] - v1[0]*v2[2]);
    res.push_back(v1[0]*v2[1] - v1[1]*v2[0]);
    return res;
};

void swap_(float* el1, float* el2){
  float swap = *el1;
  *el1 = *el2;
  *el2 = swap;
}

float ray_in_box(point* A, point* B, point* min, point* max){

  float x0 = min -> coor[0];
  float y0 = min -> coor[1];
  float z0 = min -> coor[2];

  float x1 = max -> coor[0];
  float y1 = max -> coor[1];
  float z1 = max -> coor[2];

  float x = A -> coor[0];
  float y = A -> coor[1];
  float z = A -> coor[2];

  point* vector = new point(0,0,0);


  float swap;
  float len = 0;

  for (int i = 0; i < 3; i++){
    vector -> coor[i] = B -> coor[i] - A -> coor[i];
    len += ((vector -> coor[i])*(vector -> coor[i]));
  }

  len = sqrt(len);

  for (int i = 0; i < 3; i++){
    vector -> coor[i] /= len;
  }

  float Tnear = - INT_MAX;
  float Tfar = INT_MAX;

  if (vector -> coor[0] == 0){
    if (x > x1 || x < x0){
      return INT_MAX;
    }
  } else {
    Tnear = (x0 - x) / vector -> coor[0];
    Tfar = (x1 - x) / vector -> coor[0];
    if (Tnear > Tfar) swap_(&Tnear, &Tfar);
  }

  if (vector -> coor[1] == 0){
    if (y > y1 || y < y0){
      return INT_MAX;
    }
  } else {
    float T1y = (y0 - y) / vector -> coor[1];
    float T2y = (y1 - y) / vector -> coor[1];

    if (T1y > T2y) swap_(&T1y, &T2y);
    if (T1y > Tnear) Tnear = T1y;
    if (T2y < Tfar) Tfar = T2y;
  }

  if (Tnear > Tfar || Tfar < 0) return INT_MAX;

  if (vector -> coor[2] == 0){
    if (z > z1 || z < z0){
      return INT_MAX;
    }
  } else {
    float T1z = (z0 - z) / vector -> coor[2];
    float T2z = (z1 - z) / vector -> coor[2];

    if (T1z > T2z) swap_(&T1z, &T2z);
    if (T1z > Tnear) Tnear = T1z;
    if (T2z < Tfar) Tfar = T2z;
  }

  if (Tnear > Tfar || Tfar == 0) return INT_MAX;

  return Tnear;

}


int SAH(vector<flat*> elms, float min, float max, int axis){
  int count = elms.size();
  int answer = 0;
  float result = INT_MAX;
  quick_sort_first(elms, 0, elms.size() - 1, axis);
  int curr;
  for (int i = 0; i < count; i++){
    curr = (elms[i] -> min_p -> coor[axis] - min)*i + (max - elms[i] -> max_p -> coor[axis])*(count - i);
    if (curr < result){
      result = curr;
      answer = i;
    }
  }
  return answer;
}
