#include "flat.h"

using namespace std;

float comparator(float i1, float i2, float i3, int param){ // 0 - знайти найменше, 1 - найбільше
  if (param == 1){
    if (i1 > i2 && i1 > i3) return i1;
    else return i2 > i3 ? i2 : i3;
  } else if (param == 0){
    if (i1 < i2 && i1 < i3) return i1;
    else return i2 < i3 ? i2 : i3;
  }
}
