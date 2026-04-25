#include <bits/stdc++.h>
// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/tree_policy.hpp>
using namespace std;
// using namespace __gnu_pbds;

typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef tuple<int, ll, ll> edge;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<vi> vvi;

#define LSOne(S) ((S) & -(S))
// int two_pow_p1 = LSOne(mask);
// int p1 = __builtin_ctz(two_pow_p1);
#define REP(i, s, t) for (int i = (s); i < (t); ++i)

const int INF = 1e9;
template <class T> T read() {
  T v;
  std::cin >> v;
  return v;
}

void fast_io() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
}

struct DSU {
  vi e;
  DSU(int n) : e(n + 1, -1) {};
  int get(int x) { return (e[x] < 0 ? x : e[x] = get(e[x])); }
  int unite(int x, int y) {
    x = get(x), y = get(y);
    if (x == y)
      return 0;
    if (e[x] > e[y])
      swap(x, y);
    e[x] += e[y];
    e[y] = x;
    return 1;
  }
};

void solve() {
  int n, m;
  cin >> n >> m;

  vvi cost(n + 1, vi(n + 1, INF));
  DSU dsu(n);

  for (int i = 0; i < m; ++i) {
    int p, q, c;
    cin >> p >> q >> c;
    cost[p][q] = c;
    cost[q][p] = c;
    dsu.unite(p, q);
  }

  map<int, vi> components;
  for (int i = 1; i <= n; ++i) {
    components[dsu.get(i)].push_back(i);
  }

  ll res = 0;

  for (auto const &[root, nodes] : components) {
    int K = nodes.size();

    if (K % 2 != 0) {
      cout << "impossible\n";
      return;
    }

    if (K > 30) {
      cout << "impossible\n";
      return;
    }

    vi memo(1 << K, -1);

    auto solve_dp = [&](auto &self, int mask) -> int {
      if (mask == 0)
        return 0;
      if (memo[mask] != -1)
        return memo[mask];

      int ans = INF;

      int u_idx = __builtin_ctz(mask);
      int u = nodes[u_idx];
      for (int v_idx = u_idx + 1; v_idx < K; ++v_idx) {
        if (mask & (1 << v_idx)) {
          int v = nodes[v_idx];

          if (cost[u][v] != INF) {
            int sub_cost = self(self, mask ^ (1 << u_idx) ^ (1 << v_idx));

            if (sub_cost != INF) {
              ans = min(ans, cost[u][v] + sub_cost);
            }
          }
        }
      }
      return memo[mask] = ans;
    };

    int comp_cost = solve_dp(solve_dp, (1 << K) - 1);

    if (comp_cost >= INF) {
      cout << "impossible\n";
      return;
    }

    res += comp_cost;
  }
  cout << res << "\n";
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
