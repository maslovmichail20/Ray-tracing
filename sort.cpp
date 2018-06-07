#include <fstream>
#include <iostream>
#include "flat.h"

using namespace std;

// void swap(flat** a, flat** b){ // функція для обміну елементів масиву місцями
//   flat* swap = *a;
//   *a = *b;
//   *b = swap;
// }
//
// void sort_without_decompose(int* arr, int f, int l, int* count){ // викликаємо, коли у підмасиві менше 4 елементів
//   if ((l - f) == 1){
//     (*count)++;
//     if (arr[f] > arr[l]){
//       swap(&arr[l], &arr[f]);
//     }
//     return;
//   }
//   if ((l - f) == 2){
//     int i = f - 1;
//     int x = arr[l];
//     for (int j = f; j < l; j++){
//       (*count)++;
//       if (arr[j] <= x){
//         i++;
//         swap(&arr[i], &arr[j]);
//       }
//     }
//     arr[l] = arr[i + 1];
//     arr[i + 1] = x;
//     if (i == -1){
//       (*count)++;
//       if (arr[f + 1] > arr[f + 2]) swap(&arr[f + 1], &arr[f + 2]);
//       return;
//     }
//     if (i == l - 1){
//       (*count)++;
//       if (arr[f] > arr[f + 1]) swap(&arr[f], &arr[f + 1]);
//       return;
//     }
//     return;
//   }
// }


int partition_first(vector<flat*>& arr, int f, int l, int axis){
  int i = f - 1;
  flat* x = arr[l];
  for (int j = f; j < l; j++){
    if (arr[j] -> min_p -> coor[axis] <= x-> min_p -> coor[axis]){
      i++;
      flat* swap = arr[i];
      arr[i] = arr[j];
      arr[j] = swap;
      //swap(&arr[i], &arr[j]);
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
