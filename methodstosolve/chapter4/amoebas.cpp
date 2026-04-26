#include <bits/stdc++.h>

// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/tree_policy.hpp>
using namespace std;

// using namespace __gnu_pbds;

typedef long long ll;
typedef vector<int> vi;
typedef vector<string> vs;
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

int m, n;
vs grid;
vector<vector<bool>> visited;

int dr[] = {-1, -1, -1, 0, 0, 1, 1, 1};

int dc[] = {-1, 0, 1, -1, 1, -1, 0, 1};

void bfs(int r, int c) {
  queue<ii> q;
  q.push({r, c});
  visited[r][c] = true;

  while (!q.empty()) {
    ii curr = q.front();
    q.pop();

    for (int i = 0; i < 8; ++i) {
      int nr = curr.first + dr[i];
      int nc = curr.second + dc[i];

      if (nr >= 0 && nr < m && nc >= 0 && nc < n && grid[nr][nc] == '#' &&
          !visited[nr][nc]) {
        visited[nr][nc] = true;
        q.push({nr, nc});
      }
    }
  }
}

void solve() {
  cin >> m >> n;

  grid.resize(m);
  visited.assign(m, vector<bool>(n, false));

  for (int i = 0; i < m; ++i) {
    cin >> grid[i];
  }

  int count = 0;

  for (int i = 0; i < m; ++i) {

    for (int j = 0; j < n; ++j) {

      if (grid[i][j] == '#' && !visited[i][j]) {
        count++;
        bfs(i, j);
      }
    }
  }
  cout << count << "\n";
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
