#include <bits/stdc++.h>
// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/tree_policy.hpp>
using namespace std;
// using namespace __gnu_pbds;

typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef tuple<int, ll, ll> edge;
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

void fast_io() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
}
const ll INF_FLOW = 1e18;
const double INF_COST = 1e18;

struct MCMFEdge {
  int v;
  ll cap, flow;
  double cost;
};

class MCMF {
private:
  int V;
  vector<MCMFEdge> EL;
  vector<vi> AL;
  vector<double> dist;
  vector<ii> p;
  vector<bool> in_queue;

  bool SPFA(int s, int t) {
    dist.assign(V, INF_COST);
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
        ll cap = edge.cap, flow = edge.flow;
        double cost = edge.cost;

        if (cap - flow > 0 && dist[v] > dist[u] + cost + 1e-9) {
          dist[v] = dist[u] + cost;
          p[v] = {u, idx};
          if (!in_queue[v]) {
            q.push(v);
            in_queue[v] = true;
          }
        }
      }
    }
    return dist[t] != INF_COST;
  };

public:
  MCMF(int initialV) : V(initialV) { AL.assign(V, vi()); }

  void add_edge(int u, int v, ll cap, double cost) {
    EL.push_back({v, cap, 0, cost});
    AL[u].push_back(EL.size() - 1);
    EL.push_back({u, 0, 0, -cost});
    AL[v].push_back(EL.size() - 1);
  }

  pair<ll, double> min_cost_max_flow(int s, int t) {
    ll max_flow = 0;
    double min_cost = 0;
    while (SPFA(s, t)) {
      ll f = INF_FLOW;
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

struct Hill {
  double x, y, h;
};

void solve() {
  int N, S, T;
  double Q;
  if (!(cin >> N >> S >> T >> Q))
    return;

  vector<Hill> hills(N + 1);
  for (int i = 1; i <= N; ++i) {
    cin >> hills[i].x >> hills[i].y >> hills[i].h;
  }

  int source = 0;
  int sink = N + 1;
  MCMF mcmf(sink + 1);

  for (int i = 0; i < S; ++i) {
    int s_idx;
    cin >> s_idx;
    mcmf.add_edge(source, s_idx, 1, 0.0);
  }

  for (int i = 0; i < T; ++i) {
    int t_idx;
    cin >> t_idx;
    mcmf.add_edge(t_idx, sink, 1, 0.0);
  }

  for (int i = 1; i <= N; ++i) {
    for (int j = 1; j <= N; ++j) {
      if (hills[i].h > hills[j].h) {
        double dx = hills[i].x - hills[j].x;
        double dy = hills[i].y - hills[j].y;
        double dh = hills[i].h - hills[j].h;
        double dist = sqrt(dx * dx + dy * dy + dh * dh);

        if (dist <= Q) {
          mcmf.add_edge(i, j, T, dist);
        }
      }
    }
  }

  auto result = mcmf.min_cost_max_flow(source, sink);

  if (result.first == T) {
    cout << fixed << setprecision(6) << result.second << "\n";
  } else {
    cout << "IMPOSSIBLE\n";
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
