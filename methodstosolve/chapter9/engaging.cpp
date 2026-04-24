#include <bits/stdc++.h>
// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/tree_policy.hpp>
using namespace std;
// using namespace __gnu_pbds;

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
template <class T> T read() {
  T v;
  std::cin >> v;
  return v;
}

void fast_io() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
}

pair<int, vi> hungarian(const vector<vi> &a) {
  if (a.empty())
    return {0, {}};
  int n = sz(a) + 1, m = sz(a[0]) + 1;
  vi u(n), v(m), p(m), ans(n - 1);
  rep(i, 1, n) {
    p[0] = i;
    int j0 = 0; // add "dummy" worker 0
    vi dist(m, INT_MAX), pre(m, -1);
    vector<bool> done(m + 1);
    do { // dijkstra
      done[j0] = true;
      int i0 = p[j0], j1, delta = INT_MAX;
      rep(j, 1, m) if (!done[j]) {
        auto cur = a[i0 - 1][j - 1] - u[i0] - v[j];
        if (cur < dist[j])
          dist[j] = cur, pre[j] = j0;
        if (dist[j] < delta)
          delta = dist[j], j1 = j;
      }
      rep(j, 0, m) {
        if (done[j])
          u[p[j]] += delta, v[j] -= delta;
        else
          dist[j] -= delta;
      }
      j0 = j1;
    } while (p[j0]);
    while (j0) { // update alternating path
      int j1 = pre[j0];
      p[j0] = p[j1], j0 = j1;
    }
  }
  rep(j, 1, m) if (p[j]) ans[p[j] - 1] = j - 1;
  return {-v[0], ans}; // min cost
}

void solve() {
  int m, n, k;
  cin >> m >> n >> k;
  // vvi cost(n + 1, vi(m + 1, 0));

  bool swapped = false;
  int L = n, R = m;
  if (n > m) {
    swapped = true;
    L = m;
    R = n;
  }

  vvi cost(L, vi(R, 0));

  for (int i = 0; i < k; ++i) {
    int u, v, p;
    cin >> u >> v >> p;
    u--;
    v--;
    if (!swapped) {
      cost[u][v] = -p;
    } else {
      cost[v][u] = -p;
    }
  }

  pair<int, vi> result = hungarian(cost);

  int max_satisfaction = -result.first;
  vector<pair<int, int>> final_assignments;
  for (int i = 0; i < L; ++i) {
    int j = result.second[i];
    if (cost[i][j] < 0) {
      if (!swapped) {
        final_assignments.push_back({i + 1, j + 1});
      } else {
        final_assignments.push_back({j + 1, i + 1});
      }
    }
  }

  cout << max_satisfaction << "\n";
  cout << final_assignments.size() << "\n";
  for (auto p : final_assignments) {
    cout << p.first << " " << p.second << "\n";
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
