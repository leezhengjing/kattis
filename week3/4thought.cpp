#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> ii;
typedef vector<ii> vii;

#define LSOne(S) ((S) & -(S))
// int two_pow_p1 = LSOne(mask);
// int p1 = __builtin_ctz(two_pow_p1);

void fast_io() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
}

template <typename T> vector<T> get_words() {
  string line;
  getline(std::cin, line);
  istringstream ss{line};
  ss >> boolalpha;
  vector<T> v;
  copy(istream_iterator<T>{ss}, istream_iterator<T>{}, back_inserter(v));
  return v;
}

template <typename T> void put_words(const vector<T> &v) {
  if (!v.empty()) {
    copy(v.begin(), prev(v.end()), ostream_iterator<T>{cout, " "});
    cout << v.back();
  }
  cout << '\n';
}

bool check_precedence(const int &a, const int &b) {
  if (a == 0 || a == 1) {
    return true;
  } else {
    if (b == 0 || b == 1) {
      return false;
    }
    return true;
  }
}

int operate(const int &a, const int &b, const int &binop) {
  if (binop == 0) {
    return a / b;
  } else if (binop == 1) {
    return a * b;
  } else if (binop == 2) {
    return a + b;
  } else {
    return a - b;
  }
}
void solve() {
  // cin.ignore(numeric_limits<streamsize>::max(), '\n');
  // 0: /
  // 1: *
  // 2: -
  // 3: +
  //
  int n;
  cin >> n;

  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      for (int k = 0; k < 4; ++k) {
        deque<int> operands = {4, 4, 4, 4};
        deque<int> operators = {i, j, k};
        while (!operators.empty()) {
          int next = operators.front();
          operators.pop_front();
          if (!operators.empty()) {
            if (check_precedence(next, operators.front())) {
              int first_op = operands.front();
              operands.pop_front();
              int second_op = operands.front();
              operands.pop_front();
              operands.emplace_front(operate(first_op, second_op, next));

            } else {
              int real_next = operators.front();
              operators.pop_front();
              operators.emplace_front(next);
              int first_op = operands.front();
              operands.pop_front();
              int second_op = operands.front();
              operands.pop_front();
              operands.emplace_front(operate(first_op, second_op, next));
            }
          }
        }
        cout << operands.front() << endl;
      }
    }
  }
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;

  while (t--) {
    // code here
    solve();
  }

  // reading input
  // read int: int n; cin >> n;
  // read line: string s; getline(cin, s);
  // read list/arr: vi arr(n); for(int i=0; i<n; ++i) cin >> arr[i];
  // eof reading: int n; while(cin >> n) { ... }

  return 0;
}
