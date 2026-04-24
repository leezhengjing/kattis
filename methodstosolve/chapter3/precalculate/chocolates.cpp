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

struct Coordinate {
  int r;
  int c;
  Coordinate(int r, int c) : r(r), c(c) {}
};

vector<Coordinate> get_neighbors(Coordinate cell, int num_rows, int num_cols) {
  vector<Coordinate> neighbors;
  array<int, 4> delta_row = {-1, 0, 1, 0};
  array<int, 4> delta_col = {0, 1, 0, -1};
  for (int i = 0; i < 4; i++) {
    int neighbor_row = cell.r + delta_row[i];
    int neighbor_col = cell.c + delta_col[i];
    if (0 <= neighbor_row && neighbor_row < num_rows && 0 <= neighbor_col &&
        neighbor_col < num_cols) {
      neighbors.emplace_back(neighbor_row, neighbor_col);
    }
  }
  return neighbors;
}

vector<Coordinate> get_neighbors_8(Coordinate cell, int num_rows,
                                   int num_cols) {
  vector<Coordinate> neighbors;
  array<int, 8> delta_row = {
      -1, -1, -1, 1, 1, 1, 0, 0,
  };
  array<int, 8> delta_col = {-1, 0, 1, -1, 0, 1, -1, 1};
  for (int i = 0; i < 8; i++) {
    int neighbor_row = cell.r + delta_row[i];
    int neighbor_col = cell.c + delta_col[i];
    if (0 <= neighbor_row && neighbor_row < num_rows && 0 <= neighbor_col &&
        neighbor_col < num_cols) {
      neighbors.emplace_back(neighbor_row, neighbor_col);
    }
  }
  return neighbors;
}

void bfs(vvi &grid, Coordinate root, int num_rows, int num_cols, int target,
         bool use_8) {
  queue<Coordinate> q;
  q.push(root);
  grid[root.r][root.c] = ~target;
  while (!q.empty()) {
    Coordinate node = q.front();
    vector<Coordinate> neighbors =
        use_8 ? get_neighbors_8(node, num_rows, num_cols)
              : get_neighbors(node, num_rows, num_cols);
    for (Coordinate neighbor : neighbors) {
      if (grid[neighbor.r][neighbor.c] == ~target)
        continue;

      if (grid[neighbor.r][neighbor.c] != target) {
        continue;
      }
      q.push(neighbor);
      grid[neighbor.r][neighbor.c] = ~target;
    }
    q.pop();
  }
}

int count_number_of_islands(vvi grid, int target) {
  int num_rows = grid.size();
  int num_cols = grid[0].size();
  int count = 0;
  // bfs starting from each unvisited land cell
  for (int r = 0; r < num_rows; r++) {
    for (int c = 0; c < num_cols; c++) {
      if (grid[r][c] == target) {
        bfs(grid, Coordinate(r, c), num_rows, num_cols, target, false);
        count++;
      }
    }
  }
  return count;
}

int count_number_of_holes(vvi grid, int target) {
  int num_rows = grid.size();
  int num_cols = grid[0].size();
  int count = 0;

  vvi padded_grid(num_rows + 2, vi(num_cols + 2, 0));

  for (int r = 0; r < num_rows; r++) {
    for (int c = 0; c < num_cols; c++) {
      padded_grid[r + 1][c + 1] = grid[r][c];
    }
  }
  for (int r = 0; r < num_rows + 2; r++) {
    for (int c = 0; c < num_cols + 2; c++) {
      if (padded_grid[r][c] == target) {
        bfs(padded_grid, Coordinate(r, c), num_rows + 2, num_cols + 2, target,
            true);
        count++;
      }
    }
  }
  return count;
}

void solve() {
  // cin.ignore(numeric_limits<streamsize>::max(), '\n');
  int R, C;
  cin >> R >> C;
  int res = 0;
  for (int i = 1; i < (1 << R * C); ++i) {
    int bitmask = i;
    int idx = 0;
    vvi grid(R, vi(C, 0));
    for (int r = 0; r < R; ++r) {
      for (int c = 0; c < C; ++c) {
        if ((1 << idx) & bitmask) {
          grid[r][c] = 1;
        }
        ++idx;
      }
    }
    if (count_number_of_islands(grid, 1) == 1 &&
        count_number_of_holes(grid, 0) == 1) {
      ++res;
    }
  }
  cout << res << "\n";
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
