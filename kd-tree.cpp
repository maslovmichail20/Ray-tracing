#include <iostream>
#include <vector>
#include "limits.h"

using namespace std;

int comparator(int i1, int i2, int i3, int param){ // 1 - знайти найбільше, 0 - найменше
  if (param == 1){
    if (i1 > i2 && i1 > i3) return i1;
    else return i2 > i3 ? i2 : i3;
  } else if (param == 0){
    if (i1 < i2 && i1 < i3) return i1;
    else return i2 < i3 ? i2 : i3;
  }
}

struct point{
  int *coor = new int[3];
  point(){
    coor[0] = 0;
    coor[1] = 0;
    coor[2] = 0;
  }
  point(int x, int y, int z){
    coor[0] = x;
    coor[1] = y;
    coor[2] = z;
  }
};

struct flat{
  point* p1;
  point* p2;
  point* p3;
  point* min_p;
  point* max_p;
  flat(point* _p1, point* _p2, point* _p3){
    min_p = new point();
    max_p = new point();
    p1 = _p1;
    p2 = _p2;
    p3 = _p3;
    for (int i = 0; i < 3; i++){
      min_p -> coor[i] = comparator(_p1 -> coor[i], _p2 -> coor[i], _p3 -> coor[i], 0);
      max_p -> coor[i] = comparator(_p1 -> coor[i], _p2 -> coor[i], _p3 -> coor[i], 1);
    }
  }
};

int SAH(vector<flat*> elms, int min, int max, int axis){
  int count = elms.size();
  int answer = 0;
  int result = INT_MAX;
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

int extr(vector<flat*> elms, int axis, int param){
  int result = param ? INT_MIN : INT_MAX;
  for (int i = 0; i < elms.size(); i++){
    if (elms[i] -> min_p -> coor[axis] < result && !param) result = elms[i] -> min_p -> coor[axis];
    if (elms[i] -> max_p -> coor[axis] > result && param) result = elms[i] -> max_p -> coor[axis];
  }
  return result;
}

struct node{
  int axis;
  int min;
  int max;
  vector<flat*> elements;
  //flat **elements;
  int delimiter;
  node* left;
  node* right;
  node (int a, int _min, int _max){
    axis = a;
    min = _min;
    max = _max;
  }
};

void build_tree(vector<flat*> elms, node* obj, int axis){
  cout << "NEW NODE" << axis << endl;
  obj -> delimiter = SAH(elms, obj -> min, obj -> max, axis);
  int delim = obj -> delimiter;
  vector<flat*> l;
  vector<flat*> r;
  for (int i = 0; i < elms.size(); i++){
    if (elms[i] -> max_p -> coor[axis] <= delim){
      l.push_back(elms[i]);
    }
    if (elms[i] -> min_p -> coor[axis] >= delim){
      r.push_back(elms[i]);
    }
    if (elms[i] -> min_p -> coor[axis] < delim && elms[i] -> max_p -> coor[axis] > delim){
      cout << i << endl;
      l.push_back(elms[i]);
      r.push_back(elms[i]);
    }
  }
  cout << delim <<" " <<axis<<  endl;
  if (elms.size() > 1){
    ///cout << obj -> left << endl;
    int n_ax = axis == 2 ? 0 : ++axis;
    obj -> left = new node(n_ax, extr(l, n_ax, 0), extr(l, n_ax, 1));
    obj -> right = new node(n_ax, extr(r, n_ax, 0), extr(r, n_ax, 1));
    // cout << obj -> left << endl;
    build_tree(l, obj -> left, n_ax);
    build_tree(r, obj -> right, n_ax);
  } else {
    obj -> elements = elms;
  }
}

int main(){
  point* p1 = new point(0,0,0);
  point* p2 = new point(0,3,0);
  point* p3 = new point(0,0,3);
  point* p4 = new point(3,0,0);
  point* p5 = new point(3,3,2);
  point* p6 = new point(2,3,0);

  vector<flat*> v;
  v.push_back(new flat(p1, p2, p3));
  v.push_back(new flat(p4, p5, p6));

  node* root = new node(0, 0, 3);

  build_tree(v, root, 0);

  cout << root << endl;
  //cout << root -> left -> elements[0] << endl;
  //cout << v[0] <<endl;
  //cout << root -> right << endl;
   return 0;
}
