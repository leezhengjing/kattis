#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef tuple<int, ll, ll> edge; // For MaxFlow
typedef vector<int> vi;
typedef pair<int, int> ii;

const ll INF = 1e18;

// ==========================================
// 1. MAX FLOW & MIN CUT (EK & Dinic Hybrid)
// ==========================================
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

struct Edge {
  int to;
  int cap;
  int flow;
  int rev; // Index of the reverse edge in adj[to]
};

// ==========================================
// 2. FAST MAX-FLOW (Using adj list instead of EL)
// ==========================================

class FastMaxFlow {
private:
  int V;
  vector<vector<Edge>> adj; // 2. Direct adjacency list
  vector<int> d, last;

  bool BFS(int s, int t) {
    fill(d.begin(), d.end(), -1);
    d[s] = 0;
    queue<int> q({s});

    while (!q.empty()) {
      int u = q.front();
      q.pop();
      if (u == t)
        break;

      for (auto &edge : adj[u]) {
        if (edge.cap - edge.flow > 0 && d[edge.to] == -1) {
          d[edge.to] = d[u] + 1;
          q.push(edge.to);
        }
      }
    }
    return d[t] != -1;
  }

  int DFS(int u, int t, int f) {
    if (u == t || f == 0)
      return f;

    for (int &i = last[u]; i < adj[u].size(); ++i) {
      auto &edge = adj[u][i];
      if (d[edge.to] != d[u] + 1)
        continue;

      if (int pushed = DFS(edge.to, t, min(f, edge.cap - edge.flow))) {
        edge.flow += pushed;
        adj[edge.to][edge.rev].flow -= pushed; // 3. Fast reverse edge access
        return pushed;
      }
    }
    return 0;
  }

public:
  FastMaxFlow(int initialV) : V(initialV) {
    adj.assign(V, vector<Edge>());
    d.resize(V);
    last.resize(V);
  }

  void reserve_edges(int u, int expected_edges) {
    adj[u].reserve(expected_edges);
  }

  void add_edge(int u, int v, int cap) {
    // Add forward edge
    adj[u].push_back({v, cap, 0, (int)adj[v].size()});
    // Add residual reverse edge. If v == u, size is -1 to handle self-loops
    // safely
    adj[v].push_back({u, 0, 0, (int)adj[u].size() - 1});
  }

  int dinic(int s, int t) {
    int mf = 0;
    const int INF = 1e9; // int instead of ll
    while (BFS(s, t)) {
      fill(last.begin(), last.end(), 0);
      while (int f = DFS(s, t, INF)) {
        mf += f;
      }
    }
    return mf;
  }
};

// ==========================================
// 2. MIN-COST MAX-FLOW (SPFA)
// ==========================================
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

int main() {
  // Example usage
  // MaxFlow mf(nodes);
  // mf.add_edge(u, v, cap);
  // ll flow = mf.dinic(S, T);

  // MCMF mcmf(nodes);
  // mcmf.add_edge(u, v, cap, cost);
  // pair<ll, ll> res = mcmf.min_cost_max_flow(S, T);
  return 0;
}
