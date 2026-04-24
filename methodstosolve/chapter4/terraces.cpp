#include <bits/stdc++.h>

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
const int MOD = 1e9 + 7;

void fast_io() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
}

vvi grid;
vi visited;
int n, m;
int dr[] = {-1, 1, 0, 0};
int dc[] = {0, 0, 1, -1};
int dfs(int r, int c, int initial) {
  // vii neighbors;
  int count = 0;

  if (grid[r][c] == initial)
    count++;

  for (int i = 0; i < 4; ++i) {
    int nr = r + dr[i];
    int nc = c + dc[i];

    if (nr >= 0 && nr < m && nc >= 0 && nc < n) {
      if (visited[nr * n + nc])
        continue;
      if (grid[nr][nc] >= grid[r][c]) {
        visited[nr * n + nc] = true;
        count += dfs(nr, nc, initial);
      }
    }
  }
  // return neighbors;
  return count;
}

void solve() {

  cin >> n >> m;

  grid.resize(m, vi(n));
  visited.resize(m * n, false);

  vector<pair<int, ii>> starts;

  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < n; ++j) {
      cin >> grid[i][j];
      // if (grid[i][j] == 0)
      //   starts.push_back({i, j});
      starts.push_back({grid[i][j], {i, j}});
    }
  }

  sort(starts.begin(), starts.end());

  int numCC = 0;

  for (auto &[val, coords] : starts) {
    int i = coords.first;
    int j = coords.second;
    if (visited[i * n + j])
      continue;
    visited[i * n + j] = true;
    numCC += dfs(i, j, grid[i][j]);
  }

  cout << numCC << "\n";
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
