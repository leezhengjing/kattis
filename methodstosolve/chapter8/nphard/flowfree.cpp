#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
// typedef tuple<int, ll, ll> edge;
typedef tuple<int, ll, ll, ll> edge;
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

string grid[4];
struct Point {
  int r, c;
};
vector<Point> blanks;
vector<char> active_c;
map<char, vector<Point>> endpoints;

int dr[] = {-1, 1, 0, 0};
int dc[] = {0, 0, -1, 1};

int get_longest_path(int r, int c, int tr, int tc, char col, int visited) {
  if (r == tr && c == tc)
    return 1;

  int max_len = -1000;
  for (int i = 0; i < 4; ++i) {
    int nr = r + dr[i];
    int nc = c + dc[i];

    if (nr >= 0 && nr < 4 && nc >= 0 && nc < 4 && grid[nr][nc] == col) {
      int bit = 1 << (nr * 4 + nc);
      if (!(visited & bit)) {
        int len = get_longest_path(nr, nc, tr, tc, col, visited | bit);
        if (len > 0) {
          max_len = max(max_len, 1 + len);
        }
      }
    }
  }
  return max_len;
}

bool check_paths() {
  for (char col : active_c) {
    int total_cells = 0;
    for (int r = 0; r < 4; ++r) {
      for (int c = 0; c < 4; ++c) {
        if (grid[r][c] == col)
          total_cells++;
      }
    }

    Point start = endpoints[col][0];
    Point end = endpoints[col][1];

    int initial_visited = 1 << (start.r * 4 + start.c);
    int path_len =
        get_longest_path(start.r, start.c, end.r, end.c, col, initial_visited);
    if (path_len != total_cells)
      return false;
  }
  return true;
}

bool solve(int idx) {
  if (idx == blanks.size()) {
    return check_paths();
  }

  for (char col : active_c) {
    grid[blanks[idx].r][blanks[idx].c] = col;
    if (solve(idx + 1))
      return true;
  }

  grid[blanks[idx].r][blanks[idx].c] = 'W';
  return false;
}

int main() {
  fast_io();

  for (int i = 0; i < 4; ++i) {
    cin >> grid[i];
  }

  bool seen[256] = {false};

  for (int r = 0; r < 4; ++r) {
    for (int c = 0; c < 4; ++c) {
      char ch = grid[r][c];
      if (ch == 'W')
        blanks.push_back({r, c});
      else {
        endpoints[ch].push_back({r, c});
        if (!seen[ch]) {
          active_c.push_back(ch);
          seen[ch] = true;
        }
      }
    }
  }

  if (solve(0)) {
    cout << "solvable\n";
  } else {
    cout << "not solvable\n";
  }
  return 0;
}
