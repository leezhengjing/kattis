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
typedef tuple<int, int, int> iii;

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

enum { TOP = 0, BOTTOM, NORTH, SOUTH, EAST, WEST };

vvi edges = {
    {NORTH, SOUTH, EAST, WEST},  {SOUTH, NORTH, WEST, EAST},
    {BOTTOM, TOP, NORTH, NORTH}, {TOP, BOTTOM, SOUTH, SOUTH},
    {EAST, EAST, BOTTOM, TOP},   {WEST, WEST, TOP, BOTTOM},
};

// dr arrays is corresponding to roll north, roll south, roll east, roll west
int dr[] = {-1, 1, 0, 0};
int dc[] = {0, 0, 1, -1};

// Visited state: [row][col][top_face_val][north_face_val]
// bool visited[30][30][7][7];
bool visited[25][25][6];
vector<string> grid;

void solve() {
  int n;
  cin >> n;
  grid.resize(n);
  int startR, startC;
  for (int i = 0; i < n; ++i) {
    cin >> grid[i];
    for (int j = 0; j < n; ++j) {
      if (grid[i][j] == 'S') {
        startR = i;
        startC = j;
      }
    }
  }

  memset(visited, 0, sizeof(visited));

  queue<tuple<int, int, int>> q;
  q.push({startR, startC, WEST});
  visited[startR][startC][WEST] = true;

  while (!q.empty()) {
    auto [r, c, dir] = q.front();
    // tuple<int, int, int> cur = q.front();
    q.pop();

    if (grid[r][c] == 'H' && dir == BOTTOM) {
      cout << "Yes" << "\n";
      return;
    }

    for (int i = 0; i < 4; ++i) {
      int nr = r + dr[i];
      int nc = c + dc[i];

      if (nr >= 0 && nr < n && nc >= 0 && nc < n && grid[nr][nc] != '*') {
        int nextDir = edges[dir][i];

        if (!visited[nr][nc][nextDir]) {
          visited[nr][nc][nextDir] = true;
          q.push({nr, nc, nextDir});
        }
      }
    }
  }

  cout << "No" << "\n";
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;

  while (t--) {
    solve();
  }

  return 0;
}
