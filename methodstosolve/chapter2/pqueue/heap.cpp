#include "heap.h"
#include <bits/stdc++.h>

using namespace std;

vector<int> heap = {0};

int getMax() {
  if (getSize() == 0)
    return -1;
  return heap[1];
}

int getSize() { return heap.size() - 1; }

void insert(int element) {
  heap.push_back(element);
  int curr = getSize();

  while (curr > 1 && heap[curr] > heap[curr / 2]) {
    swap(heap[curr], heap[curr / 2]);
    curr /= 2;
  }
}

void removeMax() {
  if (getSize() == 0)
    return;

  heap[1] = heap.back();
  heap.pop_back();

  int curr = 1;
  while (curr * 2 <= getSize()) {
    int left = curr * 2;
    int right = curr * 2 + 1;
    int largest = left;

    if (right <= getSize() && heap[left] < heap[right]) {
      largest = right;
    }

    if (heap[curr] >= heap[largest])
      break;
    swap(heap[curr], heap[largest]);
    curr = largest;
  }
}
