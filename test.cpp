#include <iostream>
#include "flat.h"
#include "kd-tree.h"

using namespace std;

int main() {
  point* C = new point(10, 0, 0);
  point* px = new point(9, 0.3, 0);

  point* min = new point(0, 0, 0);
  point* max = new point(0, 3, 3);

  cout << ray_in_box(C, px, min, max) << endl;

}
