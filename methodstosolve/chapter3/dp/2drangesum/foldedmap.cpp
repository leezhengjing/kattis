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

int R, C, tr, tc;

int dp[1005][1005];

int query(int r1, int c1, int r2, int c2) {
  return dp[r2 + 1][c2 + 1] - dp[r2 + 1][c1] - dp[r1][c2 + 1] + dp[r1][c1];
}

void solve() {
  for (int i = 0; i <= R; ++i)
    for (int j = 0; j <= C; ++j)
      dp[i][j] = 0;

  for (int i = 0; i < R; ++i) {
    string s;
    cin >> s;

    for (int j = 0; j < C; ++j) {
      int val = (s[j] == 'X' ? 1 : 0);
      dp[i + 1][j + 1] = dp[i][j + 1] + dp[i + 1][j] - dp[i][j] + val;
    }
  }

  int min_tiles = 1e9;

  for (int offset_r = 0; offset_r < tr; offset_r++) {
    for (int offset_c = 0; offset_c < tc; offset_c++) {
      int curr_tiles = 0;

      for (int r = -offset_r; r < R; r += tr) {
        for (int c = -offset_c; c < C; c += tc) {
          int r1 = max(0, r);
          int c1 = max(0, c);
          int r2 = min(R - 1, r + tr - 1);
          int c2 = min(C - 1, c + tc - 1);

          if (query(r1, c1, r2, c2) > 0) {
            curr_tiles++;
          }
        }
      }
      min_tiles = min(min_tiles, curr_tiles);
    }
  }

  cout << min_tiles << "\n";
}

int main() {
  fast_io();

  while (cin >> R >> C >> tr >> tc) {
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
