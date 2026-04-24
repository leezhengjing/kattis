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

struct MCMFEdge {
  int v;
  ll cap, flow, cost;
};

class MCMF {
private:
  int V;
  vector<MCMFEdge> EL;
  vector<vi> AL;
  vector<ll> dist;
  vector<ii> p;
  vector<bool> in_queue;

  bool SPFA(int s, int t) {
    dist.assign(V, INF);
    p.assign(V, {-1, -1});
    in_queue.assign(V, false);

    queue<int> q;
    dist[s] = 0;
    q.push(s);
    in_queue[s] = true;

    while (!q.empty()) {
      int u = q.front();
      q.pop();
      in_queue[u] = false;

      for (int idx : AL[u]) {
        auto &edge = EL[idx];
        int v = edge.v;
        ll cap = edge.cap, flow = edge.flow, cost = edge.cost;

        if (cap - flow > 0 && dist[v] > dist[u] + cost) {
          dist[v] = dist[u] + cost;
          p[v] = {u, idx};
          if (!in_queue[v]) {
            q.push(v);
            in_queue[v] = true;
          }
        }
      }
    }
    return dist[t] != INF;
  }

public:
  MCMF(int initialV) : V(initialV) { AL.assign(V, vi()); }

  void add_edge(int u, int v, ll cap, ll cost) {
    EL.push_back({v, cap, 0, cost});
    AL[u].push_back(EL.size() - 1);
    EL.push_back({u, 0, 0, -cost});
    AL[v].push_back(EL.size() - 1);
  }

  pair<ll, ll> min_cost_max_flow(int s, int t) {
    ll max_flow = 0, min_cost = 0;
    while (SPFA(s, t)) {
      ll f = INF;
      for (int curr = t; curr != s; curr = p[curr].first)
        f = min(f, EL[p[curr].second].cap - EL[p[curr].second].flow);

      for (int curr = t; curr != s; curr = p[curr].first) {
        int idx = p[curr].second;
        EL[idx].flow += f;
        EL[idx ^ 1].flow -= f;
        min_cost += f * EL[idx].cost;
      }
      max_flow += f;
    }
    return {max_flow, min_cost};
  }
};

void fast_io() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
}

void solve() {
  int n;
  cin >> n;
  vi a(n + 1), b(n + 1);
  for (int i = 1; i <= n; ++i) {
    cin >> a[i];
  }
  for (int i = 1; i <= n; ++i) {
    cin >> b[i];
  }

  int S = 0;
  int T = 2 * n + 1;
  MCMF mcmf(T + 1);

  for (int i = 1; i <= n; ++i) {
    mcmf.add_edge(S, i, 1, 0);
    for (int j = 1; j <= n; ++j) {
      if (b[i] <= a[j]) {
        if (i == j) {
          mcmf.add_edge(i, j + n, 1, 0);
        } else {
          mcmf.add_edge(i, j + n, 1, 1);
        }
      }
    }
  }

  for (int j = 1; j <= n; ++j) {
    mcmf.add_edge(j + n, T, 1, 0);
  }

  auto [mf, mc] = mcmf.min_cost_max_flow(S, T);

  if (mf != n)
    cout << "-1\n";
  else
    cout << n - mc << "\n";
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
