#ifndef ASSIGNMENT_6_ADM_KD_TREE_H
#define ASSIGNMENT_6_ADM_KD_TREE_H

#include <iostream>
#include <vector>
#include <climits>
#include "flat.h"
#include <cmath>
#include <unistd.h>

using namespace std;

void swap_(float* el1, float* el2){
  float swap = *el1;
  *el1 = *el2;
  *el2 = swap;
}

int SAH(vector<flat*> elms, float min, float max, int axis){
  int count = elms.size();
  int answer = 0;
  float result = INT_MAX;
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

float extr(vector<flat*> elms, int axis, int param){
  float result = param ? INT_MIN : INT_MAX;
  for (int i = 0; i < elms.size(); i++){
    if (elms[i] -> min_p -> coor[axis] < result && !param) result = elms[i] -> min_p -> coor[axis];
    if (elms[i] -> max_p -> coor[axis] > result && param) result = elms[i] -> max_p -> coor[axis];
  }
  return result;
}

struct node{
  int axis;
  point* min;
  point* max;
  vector<flat*> elements;
  float delimiter;
  node* left;
  node* right;
  node (int a, point* _min, point* _max){
    axis = a;
    min = _min;
    max = _max;
  }
};

void build_tree(vector<flat*> elms, node* obj, int axis){
  //cout << "Start" << endl;
  //cout << "wtf";
  //cout << "NODE axis: " << axis << endl;
  //cout << elms.size() << endl;
  //int delim = SAH(elms, obj -> min -> coor[axis], obj -> max -> coor[axis], axis);
  //cout << elms[0] << endl;
  //obj -> delimiter = elms[delim] -> min_p -> coor[axis];
  //cout << "found SAH" << endl;
  //cout << axis << endl;
  //cout << "wtf";
  //obj -> min ->print();
  //obj -> max ->print();
  obj -> delimiter = (obj -> min -> coor[axis] + obj -> max -> coor[axis])/2;
  //cout << obj -> delimiter << endl;
  //obj -> min -> print();
  //obj -> max -> print();
  //cout << "DELIM: " <<  obj -> delimiter << endl;
  vector<flat*> l;
  vector<flat*> r;
  for (int i = 0; i < elms.size(); i++){
    if (elms[i] -> max_p -> coor[axis] <= obj -> delimiter){
      l.push_back(elms[i]);
    }
    if (elms[i] -> min_p -> coor[axis] >= obj -> delimiter){
      r.push_back(elms[i]);
    }
    if (elms[i] -> min_p -> coor[axis] < obj -> delimiter && elms[i] -> max_p -> coor[axis] > obj -> delimiter){
      l.push_back(elms[i]);
      r.push_back(elms[i]);
    }
  }
  //cout << "left array: " << l.size() << endl;
  //cout << "right array: " << r.size() << endl;
  //sleep(1);
  //cout << "Middle" << endl;
  if (elms.size() != l.size() && elms.size() != r.size()){
    point *middle_l = new point(obj -> max -> coor[0], obj -> max -> coor[1], obj -> max -> coor[2]);
    point *middle_r = new point(obj -> min -> coor[0], obj -> min -> coor[1], obj -> min -> coor[2]);

    middle_l -> coor[axis] = obj -> delimiter;
    middle_r -> coor[axis] = obj -> delimiter;

    // cout << l.size() << endl;
    // cout << r.size() << endl;

    int n_ax = axis == 2 ? 0 : ++axis;
    obj -> left = new node(n_ax, obj -> min, middle_l);
    obj -> right = new node(n_ax, middle_r, obj -> max);
    if (l.size() > 1) build_tree(l, obj -> left, n_ax);
    if (r.size() > 1) build_tree(r, obj -> right, n_ax);
  } else {
    obj -> elements = elms;
  }
  //cout << "Finish" << endl;
}

bool RIB(point* A, point* B, point* min, point* max){
  //cout << "HERE" << endl;
  for (int i = 0; i < 3; i++){
    int j = i == 2 ? 0 : i + 1;
    int k = j == 2 ? 0 : j + 1;

    float t1 = (min -> coor[i] - A -> coor[i]) / (B -> coor[i] - A -> coor[i]);
    float t2 = (max -> coor[i] - A -> coor[i]) / (B -> coor[i] - A -> coor[i]);

    float n1_1 = t1 * (B -> coor[j] - A -> coor[j]) + A -> coor[j];
    float n1_2 = t2 * (B -> coor[j] - A -> coor[j]) + A -> coor[j];

    float n2_1 = t1 * (B -> coor[k] - A -> coor[k]) + A -> coor[k];
    float n2_2 = t2 * (B -> coor[k] - A -> coor[k]) + A -> coor[k];

    if (n1_1 >= min -> coor[j] && n1_1 <= max -> coor[j] && n2_1 >= min -> coor[k] && n2_1 <= max -> coor[k]){
      //cout << "HERE" << endl;
      return true;
    }
    if (n1_2 >= min -> coor[j] && n1_2 <= max -> coor[j] && n2_2 >= min -> coor[k] && n2_2 <= max -> coor[k]){
      //cout << "HERE" << endl;
      return true;
    }
  }
  return false;
}

// bool ray_in_box(point* A, point* B, point* min, point* max){
//   float x0 = min -> coor[0];
//   float y0 = min -> coor[1];
//   float z0 = min -> coor[2];
//
//   float x1 = max -> coor[0];
//   float y1 = max -> coor[1];
//   float z1 = max -> coor[2];
//
//   float x = A -> coor[0];
//   float y = A -> coor[1];
//   float z = A -> coor[2];
//
//   point* vector = new point(0,0,0);
//
//   float swap;
//   float len = 0;
//
//   for (int i = 0; i < 3; i++){
//     vector -> coor[i] = B -> coor[i] - A -> coor[i];
//     len += ((vector -> coor[i])*(vector -> coor[i]));
//   }
//   len = sqrt(len);
//
//   for (int i = 0; i < 3; i++){
//     vector -> coor[i] /= len;
//   }
//
//   float Tnear = - INT_MAX;
//   float Tfar = INT_MAX;
//
//   if (vector -> coor[0] == 0){
//     if (x > x1 || x < x0){
//       return false;
//     }
//   } else {
//     Tnear = (x - x0) / vector -> coor[0];
//     Tfar = (x - x1) / vector -> coor[0];
//     if (Tnear > Tfar) swap_(&Tnear, &Tfar);
//   }
//
//   if (vector -> coor[1] == 0){
//     if (y > y1 || y < y0){
//       return false;
//     }
//   }else{
//     float T1y = (y - y0) / vector -> coor[1];
//     float T2y = (y - y1) / vector -> coor[1];
//
//     if (T1y > T2y) swap_(&T1y, &T2y);
//     if (T1y > Tnear) Tnear = T1y;
//     if (T2y < Tfar) Tfar = T2y;
//   }
//
//   if (Tnear > Tfar || Tfar < 0) return false;
//
//   if (vector -> coor[2] == 0){
//     if (z > z1 || z < z0){
//       return false;
//     }
//   } else {
//     float T1z = (z - z0) / vector -> coor[2];
//     float T2z = (z - z1) / vector -> coor[2];
//
//     if (T1z > T2z) swap_(&T1z, &T2z);
//     if (T1z > Tnear) Tnear = T1z;
//     if (T2z < Tfar) Tfar = T2z;
//   }
//
//   if (Tnear > Tfar || Tfar == 0) return false;
//
//   return true;
//
// }

vector<flat*> search_in_tree(point* A, point* B, node* obj){
  // A -> print();
  // B -> print();
  // obj -> min -> print();
  // obj -> max -> print();
  // cout << "PAPAM";
  if (obj -> left == nullptr && obj -> right == nullptr){
    return obj -> elements;
  }
  //cout << "NEXT" <<endl;
  vector<flat*> result;
  if (obj -> left != nullptr && RIB(A, B, obj -> left -> min, obj -> left -> max)){
    //cout << "GOIING LEFT" << endl;
    vector<flat*> res1 = search_in_tree(A, B, obj -> left);
    result.insert(result.end(), res1.begin(), res1.end());
  }
  //cout << "NEXT" <<endl;
  if (obj -> right != nullptr && RIB(A, B, obj -> right -> min, obj -> right -> max)){
    //cout << "GOIING RIGHT" << endl;
    vector<flat*> res2 = search_in_tree(A, B, obj -> right);
    result.insert(result.end(), res2.begin(), res2.end());
  }
  //cout << "RET";
  return result;
}

#endif //ASSIGNMENT_6_ADM_KD_TREE_H
