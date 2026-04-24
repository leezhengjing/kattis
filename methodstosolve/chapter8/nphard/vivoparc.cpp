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

int N;
vvi AL;
vi color;

void fast_io() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
}

bool dfs(int u) {
  if (u == N + 1)
    return true;

  for (int c = 1; c <= 4; ++c) {
    bool is_safe = true;
    for (int v : AL[u]) {
      if (color[v] == c) {
        is_safe = false;
        break;
      }
    }
    if (is_safe) {
      color[u] = c;

      if (dfs(u + 1))
        return true;

      color[u] = 0;
    }
  }

  return false;
}

void solve() {
  int u, v;
  char slash;
  while (cin >> u >> slash >> v) {
    AL[u].push_back(v);
    AL[v].push_back(u);
  }

  dfs(1);

  for (int i = 1; i <= N; ++i) {
    cout << i << " " << color[i] << "\n";
  }
}

int main() {
  fast_io();

  cin >> N;
  AL.assign(N + 1, vi());
  color.assign(N + 1, 0);
  int t = 1;
  // cin >> t;

  while (t--) {
    solve();
  }

  return 0;
}
