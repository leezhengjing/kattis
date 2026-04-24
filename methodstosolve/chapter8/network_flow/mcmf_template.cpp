/**
 * Min-Cost Max-Flow (Successive Shortest Path using SPFA)
 * Best for CP platforms with typical bounds.
 */
#include <algorithm>
#include <iostream>
#include <queue>
#include <tuple>
#include <vector>

using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> ii;

const ll INF = 1e18;

// Using a struct for edges is cleaner than a 4-element tuple
struct Edge {
  int v;
  ll cap, flow, cost;
};

class MCMF {
private:
  int V;
  vector<Edge> EL;
  vector<vi> AL;
  vector<ll> dist;       // Distance array for shortest path (costs)
  vector<ii> p;          // Parent array: p[u] = {parent_node, edge_index}
  vector<bool> in_queue; // Tracks if a node is in the SPFA queue

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
        ll cap = edge.cap;
        ll flow = edge.flow;
        ll cost = edge.cost;

        // Relaxation: If there is capacity AND taking this edge lowers the cost
        // to 'v'
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
    return dist[t] != INF; // True if we found a path to the sink
  }

public:
  MCMF(int initialV) : V(initialV) { AL.assign(V, vi()); }

  void add_edge(int u, int v, ll cap, ll cost) {
    // Forward edge: capacity = cap, cost = cost
    EL.push_back({v, cap, 0, cost});
    AL[u].push_back(EL.size() - 1);

    // Backward edge: capacity = 0, cost = -cost (Refund!)
    EL.push_back({u, 0, 0, -cost});
    AL[v].push_back(EL.size() - 1);
  }

  pair<ll, ll> min_cost_max_flow(int s, int t) {
    ll max_flow = 0;
    ll min_cost = 0;

    // While there is a path from s to t with available capacity
    while (SPFA(s, t)) {
      ll f = INF;

      // 1. Backtrack to find the bottleneck capacity (minimum remaining
      // capacity on the path)
      for (int curr = t; curr != s; curr = p[curr].first) {
        int idx = p[curr].second;
        f = min(f, EL[idx].cap - EL[idx].flow);
      }

      // 2. Update the residual graph with the pushed flow
      for (int curr = t; curr != s; curr = p[curr].first) {
        int idx = p[curr].second;

        EL[idx].flow += f;     // Add flow to forward edge
        EL[idx ^ 1].flow -= f; // Subtract flow from backward edge (XOR 1 trick)

        min_cost += f * EL[idx].cost; // Accumulate cost
      }
      max_flow += f;
    }

    return {max_flow, min_cost};
  }
};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int n, m, s, t;
  if (!(cin >> n >> m >> s >> t))
    return 0;

  MCMF graph(n);
  for (int i = 0; i < m; ++i) {
    int u, v;
    ll cap, cost;
    cin >> u >> v >> cap >> cost;
    graph.add_edge(u, v, cap, cost);
  }

  pair<ll, ll> result = graph.min_cost_max_flow(s, t);
  cout << "Max Flow: " << result.first << ", Min Cost: " << result.second
       << "\n";

  return 0;
}
