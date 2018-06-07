#ifndef ASSIGNMENT_6_ADM_KD_TREE_H
#define ASSIGNMENT_6_ADM_KD_TREE_H

#include <iostream>
#include <vector>
#include <climits>
#include "flat.h"
#include <cmath>
#include <unistd.h>
#include "sort.cpp"

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
    left = nullptr;
    right = nullptr;
  }
};

void build_tree(vector<flat*> elms, node* obj, int axis, int *count){
  (*count)++;
  cout << elms.size() << endl;
  quick_sort_first(elms, 0, elms.size() - 1, axis);
  int middle = elms.size() / 2;
  //int delim = SAH(elms, obj -> min -> coor[axis], obj -> max -> coor[axis], axis);
  //obj -> delimiter = (obj -> min -> coor[axis] + obj -> max -> coor[axis])/2;
  obj -> delimiter = elms[middle] -> min_p -> coor[axis];
  //obj -> delimiter = elms[delim] -> min_p -> coor[axis];
  vector<flat*> l;
  vector<flat*> r;
  for (int i = 0; i < elms.size(); i++){
    if (elms[i] -> max_p -> coor[axis] < obj -> delimiter){
      l.push_back(elms[i]);
    }
    if (elms[i] -> min_p -> coor[axis] > obj -> delimiter){
      r.push_back(elms[i]);
    }
    if (elms[i] -> min_p -> coor[axis] < obj -> delimiter && elms[i] -> max_p -> coor[axis] > obj -> delimiter){
      obj -> elements.push_back(elms[i]);
    }
  }

  if (l.size() != 0 && r.size() != 0){
    point *middle_l = new point(obj -> max -> coor[0], obj -> max -> coor[1], obj -> max -> coor[2]);
    point *middle_r = new point(obj -> min -> coor[0], obj -> min -> coor[1], obj -> min -> coor[2]);

    middle_l -> coor[axis] = obj -> delimiter;
    middle_r -> coor[axis] = obj -> delimiter;

    int n_ax = axis == 2 ? 0 : (axis + 1);
    obj -> left = new node(n_ax, obj -> min, middle_l);
    obj -> right = new node(n_ax, middle_r, obj -> max);
    if (l.size() > 1) build_tree(l, obj -> left, n_ax, count);
    else obj -> left -> elements = l;
    if (r.size() > 1) build_tree(r, obj -> right, n_ax, count);
    else obj -> right -> elements = r;
  } else {
    //obj -> elements = elms;
  }
}

bool RIB(point* A, point* B, point* min, point* max){
  // if (B -> coor[2] - 0){
  //   cout << endl;
  //   A -> print();
  //   B -> print();
  //   min -> print();
  //   max -> print();
  // }
  // cout << endl;
  // A -> print();
  // B -> print();
  // min -> print();
  // max -> print();
  for (int i = 0; i < 3; i++){
    int j = i == 2 ? 0 : i + 1;
    int k = j == 2 ? 0 : j + 1;

    float t1 = (min -> coor[i] - A -> coor[i]) / (B -> coor[i] - A -> coor[i]);
    float t2 = (max -> coor[i] - A -> coor[i]) / (B -> coor[i] - A -> coor[i]);
    // cout << "t1"<<i + 1<<" " << t1 << endl;
    // cout << "t2"<<i + 1<<" " << t2 << endl;
    float n1_1 = t1 * (B -> coor[j] - A -> coor[j]) + A -> coor[j];
    float n1_2 = t2 * (B -> coor[j] - A -> coor[j]) + A -> coor[j];
    // cout << "n1_1"<<i + 1<<" " << n1_1 << endl;
    // cout << "n1_2"<<i + 1<<" " << n1_2 << endl;

    float n2_1 = t1 * (B -> coor[k] - A -> coor[k]) + A -> coor[k];
    float n2_2 = t2 * (B -> coor[k] - A -> coor[k]) + A -> coor[k];
    // cout << "n2_1"<<i + 1<<" " << n2_1 << endl;
    // cout << "n2_2"<<i + 1<<" " << n2_2 << endl<<endl;

    if (n1_1 >= min -> coor[j] && n1_1 <= max -> coor[j] && n2_1 >= min -> coor[k] && n2_1 <= max -> coor[k]){
      return true;
    }
    if (n1_2 >= min -> coor[j] && n1_2 <= max -> coor[j] && n2_2 >= min -> coor[k] && n2_2 <= max -> coor[k]){
      return true;
    }
  }
  return false;
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

  //vector -> print();
  len = sqrt(len);

  for (int i = 0; i < 3; i++){
    vector -> coor[i] /= len;
  }

  //vector -> print();

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

vector<flat*> search_in_tree(point* A, point* B, node* obj){
  // if (obj -> left == nullptr && obj -> right == nullptr){
  //   return obj -> elements;
  // }
  vector<flat*> result;
  //result.insert(result.end(), obj->elements.begin(), obj->elements.end());
  vector<flat*> res1;
  vector<flat*> res2;
  if (obj -> left != nullptr && ray_in_box(A, B, obj -> left -> min, obj -> left -> max)){
    res1 = search_in_tree(A, B, obj -> left);
    result.insert(result.end(), res1.begin(), res1.end());
  }
  if (obj -> right != nullptr && ray_in_box(A, B, obj -> right -> min, obj -> right -> max)){
    res2 = search_in_tree(A, B, obj -> right);
    result.insert(result.end(), res2.begin(), res2.end());
  }
  result.insert(result.end(), obj->elements.begin(), obj->elements.end());
  return result;
}

#endif //ASSIGNMENT_6_ADM_KD_TREE_H
