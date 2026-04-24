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

const int UPPER_LIMIT = 1e8;
bool is_prime[UPPER_LIMIT];
int R, C;
int res = 0;

void sieve() {
  fill(is_prime, is_prime + UPPER_LIMIT, true);
  is_prime[0] = is_prime[1] = false;
  for (int i = 2; i * i < UPPER_LIMIT; ++i) {
    if (is_prime[i]) {
      for (int j = i * i; j < UPPER_LIMIT; j += i) {
        is_prime[j] = false;
      }
    }
  }
}

vi row_vals;
vi col_vals;
void solve(int cell_idx) {
  // cin.ignore(numeric_limits<streamsize>::max(), '\n');

  if (cell_idx == R * C) {
    res++;
    return;
  }

  int r = cell_idx / C;
  int c = cell_idx % C;

  for (int d = 0; d <= 9; ++d) {
    int next_row_val = row_vals[r] * 10 + d;
    int next_col_val = col_vals[c] * 10 + d;

    if (is_prime[next_row_val] && is_prime[next_col_val]) {
      int old_row = row_vals[r];
      int old_col = col_vals[c];
      row_vals[r] = next_row_val;
      col_vals[c] = next_col_val;

      solve(cell_idx + 1);

      row_vals[r] = old_row;
      col_vals[c] = old_col;
    }
  }
}
int result[9][9];

int main() {
  fast_io();

  sieve();

  for (int i = 1; i <= 8; ++i) {
    for (int j = 1; j <= 8; ++j) {
      res = 0;
      R = i;
      C = j;

      row_vals.assign(R, 0);
      col_vals.assign(C, 0);

      solve(0);
      result[i][j] = res;
    }
  }
  cout << "int res[9][9] = {\n";
  for (int i = 0; i <= 8; ++i) {
    cout << " {";
    for (int j = 0; j <= 8; ++j) {
      if (i == 0 || j == 0)
        cout << "0";
      else
        cout << result[i][j];
      if (j < 8)
        cout << ", ";
    }
    cout << "}";
    if (i < 8)
      cout << ",";
    cout << "\n";
  }
  cout << "};\n";

  // reading input
  // read int: int n; cin >> n;
  // read line: string s; getline(cin, s);
  // read list/arr: vi arr(n); for(int i=0; i<n; ++i) cin >> arr[i];
  // eof reading: int n; while(cin >> n) { ... }

  return 0;
}
