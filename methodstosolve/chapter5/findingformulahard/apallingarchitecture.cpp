#include <bits/stdc++.h>
#include <ios>
// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/tree_policy.hpp>
using namespace std;
// using namespace __gnu_pbds;

typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef tuple<int, ll, ll> edge;
// typedef tuple<int, ll, ll, ll> edge;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<vi> vvi;

#define LSOne(S) ((S) & -(S))
// int two_pow_p1 = LSOne(mask);
// int p1 = __builtin_ctz(two_pow_p1);
#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define sz(x) (int)(x).size()

const ll INF = 1e18;

void fast_io() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
}

void solve() {
  int h, w;
  cin >> h >> w;
  vector<string> grid(h);

  for (int i = 0; i < h; ++i) {
    cin >> grid[i];
  }

  double left_base = 1e9;
  double right_base = -1e9;
  for (int c = 0; c < w; ++c) {
    if (grid[h - 1][c] != '.') {
      if (left_base == 1e9)
        left_base = c;
      right_base = c + 1;
    }
  }

  int total_blocks = 0;
  double sum_x = 0;
  for (int r = 0; r < h; ++r) {
    for (int c = 0; c < w; ++c) {
      if (grid[r][c] != '.') {
        total_blocks++;
        sum_x += (c + 0.5);
      }
    }
  }

  double cog_x = sum_x / total_blocks;

  if (cog_x < left_base) {
    cout << "left\n";
  } else if (cog_x > right_base) {
    cout << "right\n";
  } else {
    cout << "balanced\n";
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;

  while (t--) {
    solve();
  }

  return 0;
}
