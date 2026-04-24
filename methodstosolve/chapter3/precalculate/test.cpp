#include <bits/stdc++.h>
using namespace std;

void test() { cout << "Hello\n"; }

int main() {
  thread t1(test);
  return 0;
}
