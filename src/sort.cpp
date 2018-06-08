#include "sort.h"

int partition_first(vector<flat*>& arr, int f, int l, int axis){
  int i = f - 1;
  flat* x = arr[l];
  for (int j = f; j < l; j++){
    if (arr[j] -> min_p -> coor[axis] <= x-> min_p -> coor[axis]){
      i++;
      flat* swap = arr[i];
      arr[i] = arr[j];
      arr[j] = swap;
    }
  }
  arr[l] = arr[i + 1];
  arr[i + 1] = x;
  return i + 1;
}

void quick_sort_first(vector<flat*>& arr, int f, int l, int axis){
  if (f >= l) return;
  int c = partition_first(arr, f, l, axis);
  quick_sort_first(arr, f, c - 1, axis);
  quick_sort_first(arr, c + 1, l, axis);
}
