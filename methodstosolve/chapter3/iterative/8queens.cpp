
#include <algorithm>
#include <bits/stdc++.h>
// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/tree_policy.hpp>
using namespace std;
// using namespace __gnu_pbds;

typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<vi> vvi;

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

vvi valid;
void precalculate() {
  vi queens = {0, 1, 2, 3, 4, 5, 6, 7};

  do {
    bool is_valid = true;
    for (int i = 0; i < 8; ++i) {
      for (int j = i + 1; j < 8; ++j) {
        if (abs(i - j) == abs(queens[i] - queens[j])) {
          is_valid = false;
          break;
        }
      }
      if (!is_valid) {
        break;
      }
    }
    if (is_valid) {
      valid.push_back(queens);
    }

  } while (next_permutation(queens.begin(), queens.end()));
}

void solve() {
  // cin.ignore(numeric_limits<streamsize>::max(), '\n');
  vi queens(8, -1);
  int total_queens = 0;
  bool same_row_queens = false;
  for (int i = 0; i < 8; ++i) {
    string s;
    cin >> s;
    for (int j = 0; j < 8; ++j) {
      if (s[j] == '*') {
        total_queens++;
        if (queens[i] != -1) {
          same_row_queens = true;
        }
        queens[i] = j;
      }
    }
  }

  if (total_queens != 8 || same_row_queens) {
    cout << "invalid" << "\n";
    return;
  }

  for (auto const &possible : valid) {
    if (queens == possible) {
      cout << "valid" << "\n";
      return;
    }
  }
  cout << "invalid" << "\n";
}

int main() {
  fast_io();

  int t = 1;
  precalculate();
  // cin >> t;

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
