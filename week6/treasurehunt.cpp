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

const int INF = 1e9;

void fast_io() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
}

int get_cost(char c) {
  if (c == '.' || c == 'S' || c == 'G')
    return 1;
  if (c == 'F')
    return 2;
  if (c == 'M')
    return 3;
  return INF;
}

void solve() {
  int N, M, K;
  cin >> N >> M >> K;

  vector<string> grid(N);
  int sR, sC, gR, gC;

  for (int i = 0; i < N; ++i) {
    cin >> grid[i];
    for (int j = 0; j < M; ++j) {
      if (grid[i][j] == 'S') {
        sR = i;
        sC = j;
      } else if (grid[i][j] == 'G') {
        gR = i;
        gC = j;
      }
    }
  }

  // dist[r][c] stores best {days, used_stamina};
  vector<vii> dist(N, vii(M, {INF, INF}));

  priority_queue<tuple<int, int, int, int>, vector<tuple<int, int, int, int>>,
                 greater<tuple<int, int, int, int>>>
      pq;

  dist[sR][sC] = {1, 0};
  pq.push({1, 0, sR, sC});

  int dr[] = {-1, 1, 0, 0};
  int dc[] = {0, 0, -1, 1};

  while (!pq.empty()) {
    auto [d, u, r, c] = pq.top();
    pq.pop();

    if (make_pair(d, u) > dist[r][c])
      continue;

    if (r == gR && c == gC) {
      cout << d << "\n";
      return;
    }

    for (int i = 0; i < 4; ++i) {
      int nr = r + dr[i];
      int nc = c + dc[i];

      if (nr >= 0 && nr < N && nc >= 0 && nc < M) {
        int cost = get_cost(grid[nr][nc]);

        if (cost > K)
          continue;

        int new_d, new_u;

        if (u + cost <= K) {
          new_d = d;
          new_u = u + cost;
        } else {
          new_d = d + 1;
          new_u = cost;
        }

        if (make_pair(new_d, new_u) < dist[nr][nc]) {
          dist[nr][nc] = {new_d, new_u};
          pq.push({new_d, new_u, nr, nc});
        }
      }
    }
  }

  cout << -1 << "\n";
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
