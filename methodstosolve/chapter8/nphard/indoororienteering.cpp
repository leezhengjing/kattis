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
const ll INF = 1e18;

void fast_io() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
}

int N;
ll L;
ll dist[15][15];

vll half1[1 << 14][14];
vll half2[1 << 14][14];

void dfs1(int u, int mask, ll len, int depth, int target) {
  if (depth == target) {
    half1[mask][u].push_back(len);
    return;
  }
  for (int v = 1; v < N; ++v) {
    if (!(mask & (1 << v))) {
      dfs1(v, mask | (1 << v), len + dist[u][v], depth + 1, target);
    }
  }
}

void dfs2(int u, int mask, ll len, int depth, int target) {
  if (depth == target) {
    half2[mask][u].push_back(len);
    return;
  }
  for (int v = 1; v < N; ++v) {
    if (!(mask & (1 << v))) {
      dfs2(v, mask | (1 << v), len + dist[v][u], depth + 1, target);
    }
  }
}
void solve() {
  cin >> N >> L;
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      cin >> dist[i][j];
    }
  }
  if (N <= 5) {
    if (N == 1) {
      if (L == 0)
        cout << "possible\n";
      else
        cout << "impossible\n";
      return;
    }
    vi p;
    for (int i = 1; i < N; ++i)
      p.push_back(i);
    do {
      ll cur_len = dist[0][p[0]];
      for (int i = 0; i < p.size() - 1; ++i) {
        cur_len += dist[p[i]][p[i + 1]];
      }
      cur_len += dist[p.back()][0];
      if (cur_len == L) {
        cout << "possible\n";
        return;
      }
    } while (next_permutation(p.begin(), p.end()));

    cout << "impossible\n";
    return;
  }

  int K = N / 2;

  dfs1(0, 1, 0, 0, K);
  dfs2(0, 1, 0, 0, N - 1 - K);

  int max_mask = 1 << N;

  for (int m1 = 1; m1 < max_mask; ++m1) {
    if (!(m1 & 1))
      continue;
    if (__builtin_popcount(m1) != K + 1)
      continue;

    int m2 = ((max_mask - 1) ^ m1) | 1;

    for (int v = 1; v < N; ++v) {
      if ((m2 & (1 << v)) && !half2[m2][v].empty()) {
        sort(half2[m2][v].begin(), half2[m2][v].end());
      }
    }

    for (int u = 1; u < N; ++u) {
      if (!(m1 & (1 << u)))
        continue;

      for (int v = 1; v < N; ++v) {
        if (!(m2 & (1 << v)))
          continue;

        for (ll len1 : half1[m1][u]) {
          ll target = L - len1 - dist[u][v];

          if (target < 0)
            continue;

          if (binary_search(half2[m2][v].begin(), half2[m2][v].end(), target)) {
            cout << "possible\n";
            return;
          }
        }
      }
    }
  }

  cout << "impossible\n";
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
