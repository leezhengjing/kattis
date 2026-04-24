/**
 * Dinic's Algorithm for Maximum Flow
 * Time Complexity: O(V^2 * E)
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

const ll INF = 1e18;

class MaxFlow {
private:
  int V;
  vector<edge> EL;
  vector<vi> AL;
  vi d;    // Level graph distance
  vi last; // Pointer to last explored edge in DFS

  // BFS to build Level Graph
  bool BFS(int s, int t) {
    d.assign(V, -1);
    d[s] = 0;
    queue<int> q;
    q.push(s);

    while (!q.empty()) {
      int u = q.front();
      q.pop();
      if (u == t)
        break; // Optimization: stop if t reached

      for (int idx : AL[u]) {
        auto [v, cap, flow] = EL[idx];
        if (cap - flow > 0 && d[v] == -1) {
          d[v] = d[u] + 1;
          q.push(v);
        }
      }
    }
    return d[t] != -1;
  }

  // DFS to find blocking flow
  ll DFS(int u, int t, ll f = INF) {
    if (u == t || f == 0)
      return f;

    for (int &i = last[u]; i < (int)AL[u].size(); ++i) {
      int idx = AL[u][i];
      auto [v, cap, flow] = EL[idx];

      if (d[v] != d[u] + 1)
        continue; // Only move to next level
      if (cap - flow == 0)
        continue; // No residual capacity

      if (ll pushed = DFS(v, t, min(f, cap - flow))) {
        auto &current_flow = get<2>(EL[idx]);
        auto &back_flow = get<2>(EL[idx ^ 1]);

        current_flow += pushed;
        back_flow -= pushed;
        return pushed;
      }
    }
    return 0;
  }

public:
  MaxFlow(int initialV) : V(initialV) { AL.assign(V, vi()); }

  void add_edge(int u, int v, ll w) {
    EL.emplace_back(v, w, 0); // Forward
    AL[u].push_back(EL.size() - 1);
    EL.emplace_back(u, 0, 0); // Backward
    AL[v].push_back(EL.size() - 1);
  }

  ll dinic(int s, int t) {
    ll mf = 0;
    while (BFS(s, t)) {
      last.assign(V, 0); // Reset edge pointers
      while (ll f = DFS(s, t)) {
        mf += f;
      }
    }
    return mf;
  }

  // Helper to retrieve flows for output
  vector<tuple<int, int, ll>> get_flows() {
    map<pair<int, int>, ll> flow_map;
    for (int u = 0; u < V; ++u) {
      for (int idx : AL[u]) {
        // Only look at forward edges
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

  ll max_flow_val = mf.dinic(s, t);
  vector<tuple<int, int, ll>> edges = mf.get_flows();

  cout << n << " " << max_flow_val << " " << edges.size() << "\n";
  for (auto [u, v, f] : edges) {
    cout << u << " " << v << " " << f << "\n";
  }

  return 0;
}
