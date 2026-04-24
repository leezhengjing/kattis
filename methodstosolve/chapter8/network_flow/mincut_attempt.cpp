#include <bits/stdc++.h>
// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/tree_policy.hpp>
using namespace std;
// using namespace __gnu_pbds;

typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> ii;
typedef tuple<int, ll, ll> edge; // For MaxFlow
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
    d[s] = 0; // 'd' is the level array. Source is level 0.
    queue<int> q({s});

    while (!q.empty()) {
      int u = q.front();
      q.pop();
      if (u == t)
        break; // We reached the sink!

      for (auto &idx : AL[u]) {         // Look at all edge indices for node 'u'
        auto &[v, cap, flow] = EL[idx]; // Grab the actual edge from EL

        // If the edge isn't full (cap - flow > 0) AND the node 'v' is unvisited
        // (d[v] == -1)
        if ((cap - flow > 0) && (d[v] == -1)) {
          d[v] = d[u] + 1; // Assign level to 'v' (one step further than 'u')
          q.push(v);
        }
      }
    }
    return d[t] != -1; // Return true if we found ANY valid path to the sink
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
      return f; // Base case: hit the sink, or bottleneck is 0

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

        // THE MAGIC TRICK: Get the reverse edge using XOR and subtract the flow
        // Subtracting flow on a reverse edge is mathematically identical to
        // adding capacity to it!
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

  // O(V * E^2) - Use for small graphs
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

  // O(V^2 * E) - Default to this for almost all CP problems!
  ll dinic(int s, int t) {
    ll mf = 0;
    while (BFS(s, t)) {
      last.assign(V, 0);
      while (ll f = DFS(s, t))
        mf += f;
    }
    return mf;
  }

  // Min-Cut Utility: Returns all nodes on the Source side of the cut
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
};
void solve() {
  int n, m, s, t;
  cin >> n >> m >> s >> t;

  MaxFlow mf(n);
  for (int i = 0; i < m; ++i) {
    int u, v;
    ll w;
    cin >> u >> v >> w;
    mf.add_edge(u, v, w, true);
  }

  mf.dinic(s, t);

  vector<int> cut_nodes = mf.get_min_cut_nodes(s);

  cout << cut_nodes.size() << "\n";
  for (int node : cut_nodes) {
    cout << node << "\n";
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
