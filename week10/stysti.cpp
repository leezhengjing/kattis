#include <bits/stdc++.h>
// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/tree_policy.hpp>
using namespace std;
// using namespace __gnu_pbds;

typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
// typedef tuple<int, ll, ll> edge;
typedef tuple<int, ll, ll, ll> edge;
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

void solve() {
  int N, M, K;
  cin >> N >> M >> K;

  vll slay_times(N);
  for (int i = 0; i < N; ++i) {
    cin >> slay_times[i];
  }

  vll sorted_times = slay_times;
  sort(sorted_times.begin(), sorted_times.end(), greater<ll>());

  ll fight_time = 0;
  for (int i = K; i < N; ++i) {
    fight_time += sorted_times[i];
  }

  vector<vll> dist(N, vll(N, INF));
  for (int i = 0; i < N; ++i)
    dist[i][i] = 0;

  for (int i = 0; i < M; ++i) {
    int u, v;
    ll w;
    cin >> u >> v >> w;

    --u;
    --v;
    dist[u][v] = min(dist[u][v], w);
    dist[v][u] = min(dist[v][u], w);
  }

  for (int k = 0; k < N; ++k) {
    for (int i = 0; i < N; ++i) {
      for (int j = 0; j < N; ++j) {
        if (dist[i][k] != INF && dist[k][j] != INF) {
          dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
        }
      }
    }
  }

  int max_mask = 1 << N;
  vector<vll> dp(max_mask, vll(N, INF));

  dp[1][0] = 0;
  for (int mask = 1; mask < max_mask; ++mask) {
    for (int u = 0; u < N; ++u) {
      if (dp[mask][u] == INF)
        continue;

      for (int v = 0; v < N; ++v) {
        if (!(mask & (1 << v))) {
          int next_mask = mask | (1 << v);

          dp[next_mask][v] = min(dp[next_mask][v], dp[mask][u] + dist[u][v]);
        }
      }
    }
  }

  ll res = INF;
  int full_mask = max_mask - 1;

  for (int i = 0; i < N; ++i) {
    res = min(res, dp[full_mask][i]);
  }
  cout << res + fight_time << "\n";
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
