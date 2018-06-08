#ifndef ASSIGNMENT_6_ADM_KD_TREE_H
#define ASSIGNMENT_6_ADM_KD_TREE_H

#include <vector>
#include <climits>
#include "flat.h"
#include <cmath>
#include <unistd.h>
#include "sort.h"
#include "geometry.h"

using namespace std;

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

void build_tree(vector<flat*>, node*, int, int, int*);

vector<flat*> search_in_tree(point*, point*, node*);

#endif //ASSIGNMENT_6_ADM_KD_TREE_H
