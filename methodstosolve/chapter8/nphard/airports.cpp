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
template <class T> T read() {
  T v;
  std::cin >> v;
  return v;
}

void fast_io() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
}

class MaxFlow {
private:
  int V;
  vector<edge> EL;
  vector<vi> AL;
  vi d, last;
  vector<ii> p;

  bool BFS(int s, int t) {
    d.assign(V, -1);
    d[s] = 0; // d is the level array. Source is level 0
    queue<int> q({s});

    while (!q.empty()) {
      int u = q.front();
      q.pop();
      if (u == t)
        break;

      for (auto &idx : AL[u]) {
        auto &[v, cap, flow] = EL[idx];

        if ((cap - flow > 0) && (d[v] == -1)) {
          d[v] = d[u] + 1;
          q.push(v);
        }
      }
    }
    return d[t] != -1;
  }

  ll send_one_flow(int s, int t, ll f = INF) {
    if (s == t)
      return f;
    auto &[u, idx] = p[t];
    auto &cap = get<1>(EL[idx]), &flow = get<2>(EL[idx]);
    ll pushed = send_one_flow(s, u, min(f, cap - flow));
    flow += pushed;
    auto &rflow = get<2>(EL[idx ^ 1]);
    rflow -= pushed;
    return pushed;
  }

  ll DFS(int u, int t, ll f = INF) {
    if ((u == t) || (f == 0))
      return f;

    // Look at 'last[u]'. This is the dead-end optimization!
    for (int &i = last[u]; i < (int)AL[u].size(); ++i) {
      int idx = AL[u][i];             // Get the edge index
      auto &[v, cap, flow] = EL[idx]; // Get the edge

      if (d[v] != d[u] + 1)
        continue; // Rule: Only move exactly one level forward

      // Recursively push flow. The bottleneck is the min of the current flow
      // 'f' and this edge's remaining capacity.
      if (ll pushed = DFS(v, t, min(f, cap - flow))) {

        flow += pushed; // Add flow to the forward edge

        auto &rflow = get<2>(EL[idx ^ 1]);
        rflow -= pushed;

        return pushed; // Return how much we successfully pushed up the chain
      }
    }
    return 0; // We couldn't push anything
  }

public:
  MaxFlow(int initialV) : V(initialV) {
    EL.clear();
    AL.assign(V, vi());
  }

  void add_edge(int u, int v, ll w, bool directed = true) {
    EL.emplace_back(v, w, 0);
    AL[u].push_back(EL.size() - 1);
    EL.emplace_back(u, directed ? 0 : w, 0);
    AL[v].push_back(EL.size() - 1);
  }

  ll edmonds_karp(int s, int t) {
    ll mf = 0;
    while (BFS(s, t)) {
      ll f = send_one_flow(s, t);
      if (f == 0)
        break;
      mf += f;
    }
    return mf;
  }

  ll dinic(int s, int t) {
    ll mf = 0;
    while (BFS(s, t)) {
      last.assign(V, 0);
      while (ll f = DFS(s, t))
        mf += f;
    }
    return mf;
  }
};

void solve() {
  int n, m;
  cin >> n >> m;

  vll inspection_time(n);
  for (int i = 0; i < n; ++i) {
    cin >> inspection_time[i];
  }

  vector<vll> raw_time(n, vll(n));
  vector<vll> dist(n, vll(n));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      cin >> raw_time[i][j];
      if (i == j) {
        dist[i][j] = 0;
      } else {
        dist[i][j] = raw_time[i][j] + inspection_time[j];
      }
    }
  }

  for (int k = 0; k < n; ++k) {
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
      }
    }
  }

  struct Flight {
    int u, v;
    ll t;
  };
  vector<Flight> flights(m);
  for (int i = 0; i < m; ++i) {
    cin >> flights[i].u >> flights[i].v >> flights[i].t;
    flights[i].u--;
    flights[i].v--;
  }

  int S = 2 * m;
  int T = 2 * m + 1;
  MaxFlow mf(T + 1);

  for (int i = 0; i < m; ++i) {
    mf.add_edge(S, i, 1);
    mf.add_edge(i + m, T, 1);
  }

  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < m; ++j) {
      if (i == j)
        continue;
      int u_i = flights[i].u, v_i = flights[i].v;
      ll t_i = flights[i].t;
      int u_j = flights[j].u;
      ll t_j = flights[j].t;

      ll ready_time_i = t_i + raw_time[u_i][v_i] + inspection_time[v_i];

      if (ready_time_i + dist[v_i][u_j] <= t_j) {
        mf.add_edge(i, j + m, 1);
      }
    }
  }

  int max_matching = mf.dinic(S, T);
  cout << m - max_matching << "\n";
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
