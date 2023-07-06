#include <iostream>
#include <vector>

// bubble sort
void bubble_sort(std::vector<int> &v) {
  for (int i = 0; i < v.size(); ++i) {
    for (int j = 0; j < v.size() - i - 1; ++j) {
      if (v[j] > v[j + 1]) {
        int tmp = v[j];
        v[j] = v[j + 1];
        v[j + 1] = tmp;
      }
    }
  }
}

// quick sort
void quick_sort(std::vector<int> &v, int left, int right) {
  if (left >= right) {
    return;
  }
  int i = left;
  int j = right;
  int key = v[left];
  while (i < j) {
    while (i < j && v[j] >= key) {
      --j;
    }
    v[i] = v[j];
    while (i < j && v[i] <= key) {
      ++i;
    }
    v[j] = v[i];
  }
  v[i] = key;
  quick_sort(v, left, i - 1);
  quick_sort(v, i + 1, right);
}


// mysql connection
#include <mysql/mysql.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
