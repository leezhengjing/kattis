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
#define REP(i, s, t) for (int i = (s); i < (t); ++i)

template <class T> T read() {
  T v;
  std::cin >> v;
  return v;
}

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

int grid[105][105];
int dp[105][105];
string grid_output[105];

int query(int r1, int c1, int r2, int c2) {
  return dp[r2][c2] - dp[r1 - 1][c2] - dp[r2][c1 - 1] + dp[r1 - 1][c1 - 1];
}
void solve() {
  // cin.ignore(numeric_limits<streamsize>::max(), '\n');
  int R, S, K;

  cin >> R >> S >> K;

  for (int i = 0; i < R; ++i) {
    string row;
    cin >> row;
    grid_output[i + 1] = row;
    for (int j = 0; j < S; ++j) {
      if (row[j] == '*') {
        grid[i + 1][j + 1] = 1;
      }
    }
  }

  for (int i = 1; i <= R; ++i) {
    for (int j = 1; j <= S; ++j) {
      dp[i][j] = grid[i][j] + dp[i - 1][j] + dp[i][j - 1] - dp[i - 1][j - 1];
    }
  }

  int res = 0;
  int start_r = 2, start_c = 2;
  for (int r = 2; r <= R - (K - 2); ++r) {
    for (int c = 2; c <= S - (K - 2); ++c) {
      int curr = query(r, c, r + (K - 2) - 1, c + (K - 2) - 1);
      if (curr > res) {
        res = curr;
        start_r = r;
        start_c = c - 1;
      }
    }
  }

  // cout << "start_r: " << start_r << " start_c: " << start_c << "\n";
  grid_output[start_r - 1][start_c - 1] = '+';
  grid_output[start_r - 1][start_c + (K - 2)] = '+';
  grid_output[start_r + (K - 2)][start_c - 1] = '+';
  grid_output[start_r + (K - 2)][start_c + (K - 2)] = '+';

  for (int r = start_r; r <= start_r + (K - 2) - 1; ++r) {
    grid_output[r][start_c - 1] = '|';
    grid_output[r][start_c + (K - 2)] = '|';
  }

  for (int c = start_c; c <= start_c + (K - 2) - 1; ++c) {
    grid_output[start_r - 1][c] = '-';
    grid_output[start_r + (K - 2)][c] = '-';
  }

  cout << res << "\n";

  for (int i = 1; i <= R; ++i) {
    cout << grid_output[i] << "\n";
  }
}

int main() {
  fast_io();

  int t = 1;
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
