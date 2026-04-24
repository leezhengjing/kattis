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

void fast_io() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
}

struct TrainEdge {
  int u, v;
  ll w;
};

void solve() {
  int n, m, k;
  if (!(cin >> n >> m >> k))
    return;

  vector<vector<pair<int, ll>>> adj(n + 1);
  vector<TrainEdge> edges(m);

  rep(i, 0, m) {
    int u, v;
    ll w;
    cin >> u >> v >> w;
    edges[i] = {u, v, w};
    adj[u].push_back({v, w});
    adj[v].push_back({u, w});
  }

  // 1. BFS to find all reachable nodes from Station 1
  vector<bool> vis(n + 1, false);
  queue<int> q;
  q.push(1);
  vis[1] = true;

  while (!q.empty()) {
    int u = q.front();
    q.pop();

    for (auto &edge : adj[u]) {
      int v = edge.first;
      if (!vis[v]) {
        vis[v] = true;
        q.push(v);
      }
    }
  }

  // 2. Collect all edges in this connected component
  vll cc_weights;
  rep(i, 0, m) {
    // If one endpoint is visited, the whole edge is in the connected component
    if (vis[edges[i].u]) {
      cc_weights.push_back(edges[i].w);
    }
  }

  // 3. Calculate "Cost B": Buy all edges in the connected component
  ll cost_all = INF;
  if (sz(cc_weights) >= k) {
    sort(cc_weights.begin(), cc_weights.end());
    cost_all = 0;
    rep(i, 0, k) { cost_all += cc_weights[i]; }
  } else {
    // If the whole component has < K edges, just sum all of them
    ll sum_all = 0;
    for (ll w : cc_weights)
      sum_all += w;
    cost_all = sum_all;
  }

  // 4. Calculate "Cost A": Standard Dijkstra for absolute shortest path
  vll dist(n + 1, INF);
  // priority_queue stores {distance, node}
  priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>>
      pq;

  dist[1] = 0;
  pq.push({0, 1});

  while (!pq.empty()) {
    auto [d, u] = pq.top();
    pq.pop();

    if (d > dist[u])
      continue;

    if (u == n)
      break; // Optimization: Reached destination

    for (auto &edge : adj[u]) {
      int v = edge.first;
      ll w = edge.second;

      if (dist[u] + w < dist[v]) {
        dist[v] = dist[u] + w;
        pq.push({dist[v], v});
      }
    }
  }

  // The answer is the best of the two strategies!
  ll ans = min(dist[n], cost_all);
  cout << ans << "\n";
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
