/**
 * Minimum Cut using Dinic's Algorithm
 * Logic: Run Dinic Max Flow, then BFS on Residual Graph to find S-side nodes.
 */
#include <algorithm>
#include <iostream>
#include <queue>
#include <tuple>
#include <vector>

using namespace std;

typedef long long ll;
typedef tuple<int, ll, ll> edge;
typedef vector<int> vi;

const ll INF = 1e18;

class MinCutDinic {
private:
  int V;
  vector<edge> EL;
  vector<vi> AL;
  vi d;
  vi last;

  bool BFS(int s, int t) {
    d.assign(V, -1);
    d[s] = 0;
    queue<int> q;
    q.push(s);
    while (!q.empty()) {
      int u = q.front();
      q.pop();
      if (u == t)
        break;
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

  ll DFS(int u, int t, ll f = INF) {
    if (u == t || f == 0)
      return f;
    for (int &i = last[u]; i < (int)AL[u].size(); ++i) {
      int idx = AL[u][i];
      auto [v, cap, flow] = EL[idx];
      if (d[v] != d[u] + 1)
        continue;
      if (cap - flow == 0)
        continue;
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
  MinCutDinic(int initialV) : V(initialV) { AL.assign(V, vi()); }

  void add_edge(int u, int v, ll w) {
    EL.emplace_back(v, w, 0);
    AL[u].push_back(EL.size() - 1);
    EL.emplace_back(u, 0, 0);
    AL[v].push_back(EL.size() - 1);
  }

  void dinic(int s, int t) {
    while (BFS(s, t)) {
      last.assign(V, 0);
      while (DFS(s, t)) {
      }
    }
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
        if (!vis[v] && cap - flow > 0) {
          vis[v] = true;
          visited_nodes.push_back(v);
          q.push(v);
        }
      }
    }
    return visited_nodes;
  }
};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int n, m, s, t;
  if (!(cin >> n >> m >> s >> t))
    return 0;

  MinCutDinic graph(n);
  for (int i = 0; i < m; ++i) {
    int u, v;
    ll w;
    cin >> u >> v >> w;
    graph.add_edge(u, v, w);
  }

  graph.dinic(s, t);

  vector<int> min_cut_set = graph.get_min_cut_nodes(s);

  cout << min_cut_set.size() << "\n";
  for (int node : min_cut_set) {
    cout << node << "\n";
  }

  return 0;
}
