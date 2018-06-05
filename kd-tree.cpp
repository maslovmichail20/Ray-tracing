#include <iostream>
#include <vector>
#include "limits.h"
#include "flat.h"
#include <cmath>

using namespace std;

// int comparator(int i1, int i2, int i3, int param){ // 0 - знайти найменше, 1 - найбільше
//   if (param == 1){
//     if (i1 > i2 && i1 > i3) return i1;
//     else return i2 > i3 ? i2 : i3;
//   } else if (param == 0){
//     if (i1 < i2 && i1 < i3) return i1;
//     else return i2 < i3 ? i2 : i3;
//   }
// }
//
// struct point{
//   int *coor = new int[3];
//   point(){
//     coor[0] = 0;
//     coor[1] = 0;
//     coor[2] = 0;
//   }
//   point(int x, int y, int z){
//     coor[0] = x;
//     coor[1] = y;
//     coor[2] = z;
//   }
// };
//
// struct flat{
//   point* p1;
//   point* p2;
//   point* p3;
//   point* min_p;
//   point* max_p;
//   flat(point* _p1, point* _p2, point* _p3){
//     min_p = new point();
//     max_p = new point();
//     p1 = _p1;
//     p2 = _p2;
//     p3 = _p3;
//     for (int i = 0; i < 3; i++){
//       min_p -> coor[i] = comparator(_p1 -> coor[i], _p2 -> coor[i], _p3 -> coor[i], 0);
//       max_p -> coor[i] = comparator(_p1 -> coor[i], _p2 -> coor[i], _p3 -> coor[i], 1);
//     }
//   }
// };

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
  //flat **elements;
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
  cout << "NODE axis: " << axis << endl;
  int delim = SAH(elms, obj -> min -> coor[axis], obj -> max -> coor[axis], axis);
  obj -> delimiter = elms[delim] -> min_p -> coor[axis];
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
      //cout << i << endl;
      l.push_back(elms[i]);
      r.push_back(elms[i]);
    }
  }
  if (elms.size() != l.size() && elms.size() != r.size()){
    ///cout << obj -> left << endl;
    point *middle_l = new point(obj -> max -> coor[0], obj -> max -> coor[1], obj -> max -> coor[2]);
    point *middle_r = new point(obj -> min -> coor[0], obj -> min -> coor[1], obj -> min -> coor[2]);

    middle_l -> coor[axis] = obj -> delimiter;
    middle_r -> coor[axis] = obj -> delimiter;
    int n_ax = axis == 2 ? 0 : ++axis;
    obj -> left = new node(n_ax, obj -> min, middle_l);
    obj -> right = new node(n_ax, middle_r, obj -> max);
    // cout << obj -> left << endl;
    build_tree(l, obj -> left, n_ax);
    build_tree(r, obj -> right, n_ax);
  } else {
    obj -> elements = elms;
  }
}

bool RIB(point* A, point* B, point* min, point* max){
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

bool ray_in_box(point* A, point* B, point* min, point* max){
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
      return false;
    }
  } else {
    Tnear = (x - x0) / vector -> coor[0];
    Tfar = (x - x1) / vector -> coor[0];
    if (Tnear > Tfar) swap_(&Tnear, &Tfar);
  }

  if (vector -> coor[1] == 0){
    if (y > y1 || y < y0){
      return false;
    }
  }else{
    float T1y = (y - y0) / vector -> coor[1];
    float T2y = (y - y1) / vector -> coor[1];

    if (T1y > T2y) swap_(&T1y, &T2y);
    if (T1y > Tnear) Tnear = T1y;
    if (T2y < Tfar) Tfar = T2y;
  }

  if (Tnear > Tfar || Tfar < 0) return false;

  if (vector -> coor[2] == 0){
    if (z > z1 || z < z0){
      return false;
    }
  } else {
    float T1z = (z - z0) / vector -> coor[2];
    float T2z = (z - z1) / vector -> coor[2];

    if (T1z > T2z) swap_(&T1z, &T2z);
    if (T1z > Tnear) Tnear = T1z;
    if (T2z < Tfar) Tfar = T2z;
  }

  if (Tnear > Tfar || Tfar == 0) return false;

  return true;

}




vector<flat*> search_in_tree(point* A, point* B, node* obj){
  if (obj -> left == nullptr){
    return obj -> elements;
  }
  vector<flat*> result;
  if (RIB(A, B, obj -> left -> min, obj -> left -> max)){
    vector<flat*> res1 = search_in_tree(A, B, obj -> left);
    result.insert(result.end(), res1.begin(), res1.end());
  }
  if (RIB(A, B, obj -> right -> min, obj -> right -> max)){
    vector<flat*> res2 = search_in_tree(A, B, obj -> right);
    result.insert(result.end(), res2.begin(), res2.end());
  }
  return result;
}

int main(){
  point* p1 = new point(0,0,0);
  point* p2 = new point(0,3,0);
  point* p3 = new point(0,0,3);
  point* p4 = new point(3,0,0);
  point* p5 = new point(3,3,2);
  point* p6 = new point(2,3,0);

  point* min = new point(0,0,0);
  point* max = new point(3,3,3);

  point* A = new point(3,3,4);
  point* B = new point(3,3,5);

  vector<flat*> v;
  v.push_back(new flat(p1, p2, p3));
  v.push_back(new flat(p4, p5, p6));

  node* root = new node(0, min, max);

  build_tree(v, root, 0);

  // root -> min -> print();
  // root -> max -> print();
  //
  // cout << endl;
  //
  // root -> left -> min -> print();
  // root -> left -> max -> print();
  //
  // cout << endl;
  //
  // root -> right -> min -> print();
  // root -> right -> max -> print();

  cout << ray_in_box(A, B, min, max) << endl;
  cout << RIB(A, B, min, max) << endl;

  //vector<flat*> res = search_in_tree(A, B, root);

   return 0;
}
