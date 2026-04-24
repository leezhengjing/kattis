/**
 * Edmonds-Karp Algorithm for Maximum Flow
 * Time Complexity: O(V * E^2)
 */
#include <algorithm>
#include <iostream>
#include <map>
#include <queue>
#include <tuple>
#include <vector>

using namespace std;

typedef long long ll;
typedef tuple<int, ll, ll> edge;
typedef vector<int> vi;
typedef pair<int, int> ii;

const ll INF = 1e18;

class MaxFlow {
private:
  int V;
  vector<edge> EL; // Edge List: <v, cap, flow>
  vector<vi> AL;   // Adjacency List storing indices in EL
  vector<ii> p;    // Parent vector for BFS: p[v] = {u, edge_index}

  bool BFS(int s, int t) {
    p.assign(V, {-1, -1});
    p[s] = {-2, -2}; // Mark source as visited
    queue<int> q;
    q.push(s);

    while (!q.empty()) {
      int u = q.front();
      q.pop();
      if (u == t)
        return true; // Reached sink

      for (int idx : AL[u]) {
        auto [v, cap, flow] = EL[idx];
        // Check if there is residual capacity and v is not visited
        if (cap - flow > 0 && p[v].first == -1) {
          p[v] = {u, idx};
          q.push(v);
        }
      }
    }
    return false;
  }

public:
  MaxFlow(int initialV) : V(initialV) { AL.assign(V, vi()); }

  void add_edge(int u, int v, ll w) {
    // Forward edge: u -> v, capacity w, flow 0
    EL.emplace_back(v, w, 0);
    AL[u].push_back(EL.size() - 1);

    // Backward edge: v -> u, capacity 0, flow 0
    EL.emplace_back(u, 0, 0);
    AL[v].push_back(EL.size() - 1);
  }

  ll edmonds_karp(int s, int t) {
    ll mf = 0;
    while (BFS(s, t)) {
      ll f = INF;
      // Backtrack to find bottleneck capacity
      for (int v = t; v != s; v = p[v].first) {
        int idx = p[v].second;
        auto [target, cap, flow] = EL[idx];
        f = min(f, cap - flow);
      }

      // Update residual graph
      for (int v = t; v != s; v = p[v].first) {
        int idx = p[v].second;
        auto &forward_flow = get<2>(EL[idx]);
        auto &backward_flow =
            get<2>(EL[idx ^ 1]); // XOR 1 gets the partner edge

        forward_flow += f;
        backward_flow -= f;
      }
      mf += f;
    }
    return mf;
  }

  // Helper to retrieve flows for output
  vector<tuple<int, int, ll>> get_flows() {
    map<pair<int, int>, ll> flow_map;
    // Iterate over all nodes
    for (int u = 0; u < V; ++u) {
      for (int idx : AL[u]) {
        // Only look at forward edges (even indices)
        if (idx % 2 == 0) {
          auto [v, cap, flow] = EL[idx];
          if (flow > 0) {
            flow_map[{u, v}] += flow;
          }
        }
      }
    }

    vector<tuple<int, int, ll>> result;
    for (auto const &[edge, flow] : flow_map) {
      result.emplace_back(edge.first, edge.second, flow);
    }
    return result;
  }
};

int main() {
  // Fast I/O
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int n, m, s, t;
  if (!(cin >> n >> m >> s >> t))
    return 0;

  MaxFlow mf(n);
  for (int i = 0; i < m; ++i) {
    int u, v;
    ll c;
    cin >> u >> v >> c;
    mf.add_edge(u, v, c);
  }

  ll max_flow_val = mf.edmonds_karp(s, t);
  vector<tuple<int, int, ll>> edges = mf.get_flows();

  cout << n << " " << max_flow_val << " " << edges.size() << "\n";
  for (auto [u, v, f] : edges) {
    cout << u << " " << v << " " << f << "\n";
  }

  return 0;
}
