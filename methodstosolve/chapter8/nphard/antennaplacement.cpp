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

    for (int u = 1; u <= n; ++u) {
      for (int idx : AL[u]) {
        auto [v, cap, flow] = EL[idx];

        if (flow == 1 && cap > 0 && v != 0 && v != n + m + 1) {
          matchings.push_back({u, v});
        }
      }
    }
    return matchings;
  }
};

int dr[] = {-1, 1, 0, 0};
int dc[] = {0, 0, -1, 1};

void solve() {
  int h, w;
  cin >> h >> w;
  int total_ast = 0;
  vector<string> grid(h);
  for (int i = 0; i < h; ++i) {
    cin >> grid[i];
  }

  int S = h * w;
  int T = h * w + 1;
  MaxFlow mf(T + 1);

  for (int r = 0; r < h; ++r) {
    for (int c = 0; c < w; ++c) {
      if (grid[r][c] == '*') {
        total_ast++;
        int u = r * w + c;
        if ((r + c) % 2 == 0) {
          mf.add_edge(S, u, 1);

          for (int i = 0; i < 4; ++i) {
            int nr = r + dr[i];
            int nc = c + dc[i];

            if (nr >= 0 && nr < h && nc >= 0 && nc < w && grid[nr][nc] == '*') {
              int v = nr * w + nc;
              mf.add_edge(u, v, 1);
            }
          }
        } else {
          mf.add_edge(u, T, 1);
        }
      }
    }
  }

  int max_matching = mf.dinic(S, T);
  cout << total_ast - max_matching << "\n";
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
