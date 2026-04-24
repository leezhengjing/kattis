#include <bits/stdc++.h>
// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/tree_policy.hpp>
using namespace std;
// using namespace __gnu_pbds;

typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef tuple<int, ll, ll> edge; // For MaxFlow
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<vi> vvi;

#define LSOne(S) ((S) & -(S))
// int two_pow_p1 = LSOne(mask);
// int p1 = __builtin_ctz(two_pow_p1);
#define REP(i, s, t) for (int i = (s); i < (t); ++i)

const ll INF = 1e18;
template <class T> T read() {
  T v;
  std::cin >> v;
  return v;
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
    // 1. Create the FORWARD edge: goes to 'v', capacity 'w', flow '0'
    EL.emplace_back(v, w, 0);

    // 2. Tell node 'u' to remember the index of this forward edge
    AL[u].push_back(EL.size() - 1);

    // 3. Create the BACKWARD (residual) edge: goes to 'u', capacity '0', flow
    // '0' Capacity is 0 because we haven't pushed any flow forward yet!
    EL.emplace_back(u, directed ? 0 : w, 0);

    // 4. Tell node 'v' to remember the index of this backward edge
    AL[v].push_back(EL.size() - 1);

    // 5 . idx ^ 1 lets us retrieve the forward/reverse edge
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

  vector<int> get_min_cut_nodes(int s) {
    vector<int> visited_nodes;
    vector<bool> vis(V, false);
    queue<int> q;
    q.push(s);
    vis[s] = true;
    visited_nodes.push_back(s);

    while (!q.empty()) {
      int u = q.front();
      q.pop();
      for (int idx : AL[u]) {
        auto [v, cap, flow] = EL[idx];
        if (!vis[v] &&
            cap - flow > 0) { // Only traverse edges with remaining capacity
          vis[v] = true;
          visited_nodes.push_back(v);
          q.push(v);
        }
      }
    }
    return visited_nodes;
  }

  vector<ii> get_bipartite_matchings(int n, int m) {
    vector<ii> matchings;

    // Iterate through all the nodes on the LEFT side of the bipartite graph
    // Assuming left nodes are numbered 1 to n
    for (int u = 1; u <= n; ++u) {
      for (int idx : AL[u]) {
        auto [v, cap, flow] = EL[idx];

        // If flow is 1, we used this edge!
        // We also check cap > 0 to ensure we are looking at the forward edge,
        // not the reverse residual edge.
        // We also make sure 'v' isn't the Source or Sink just in case.
        if (flow == 1 && cap > 0 && v != 0 && v != n + m + 1) {
          matchings.push_back({u, v});
        }
      }
    }
    return matchings;
  }
};
void fast_io() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
}

void solve() {
  int m, p;
  cin >> m >> p;

  int S = 0;
  int T = 100 + m + 1;

  MaxFlow mf(T + 1);
  vii missed_days;

  for (int i = 1; i <= 100; ++i) {
    mf.add_edge(S, i, p / 2);
  }
  for (int i = 1; i <= m; ++i) {
    int b, e;
    cin >> b >> e;

    for (int day = b; day <= e; ++day) {
      if (day % 7 == 6 || day % 7 == 0) {
        missed_days.push_back({day, i + 100});
        continue;
      }
      mf.add_edge(day, i + 100, 1);
    }

    mf.add_edge(i + 100, T, 1);
  }

  int res = mf.dinic(S, T);

  if (res == m) {
    cout << "fine\n";
  } else {
    for (const auto &[day, piano_idx] : missed_days) {
      mf.add_edge(day, piano_idx, 1);
    }
    res += mf.dinic(S, T);

    if (res == m) {
      cout << "weekend work\n";
    } else {
      cout << "serious trouble\n";
    }
  }
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
