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

int query(int r1, int c1, int r2, int c2) {
  return dp[r2][c2] - dp[r1 - 1][c2] - dp[r2][c1 - 1] + dp[r1 - 1][c1 - 1];
}

void solve() {
  // cin.ignore(numeric_limits<streamsize>::max(), '\n');
  int N, M;
  cin >> N >> M;

  for (int i = 0; i < M; ++i) {
    int r, c;
    cin >> r >> c;
    grid[r][c] = 1;
  }

  for (int i = 1; i <= N; ++i) {
    for (int j = 1; j <= N; ++j) {
      dp[i][j] = dp[i - 1][j] + dp[i][j - 1] - dp[i - 1][j - 1] + grid[i][j];
    }
  }

  int res = 0;

  for (int h = 1; h <= M; ++h) {
    if (M % h == 0) {
      int w = M / h;

      if (h > N || w > N)
        continue;

      for (int r = 1; r <= N - h + 1; ++r) {
        for (int c = 1; c <= N - w + 1; ++c) {
          int curr = query(r, c, r + h - 1, c + w - 1);
          res = max(res, curr);
        }
      }
    }
  }

  cout << M - res << "\n";
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
