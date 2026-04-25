
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
const int MAXN = 200000 + 5;

bool visited[MAXN];
vvi AL(MAXN, vi());

void dfs(int u) {
  for (int v : AL[u]) {
    if (visited[v])
      continue;
    visited[v] = true;
    dfs(v);
  }
}

void solve() {
  int n, m;
  cin >> n >> m;

  for (int i = 0; i < m; ++i) {
    int u, v;
    cin >> u >> v;
    AL[u].push_back(v);
    AL[v].push_back(u);
  }

  dfs(1);
  visited[1] = true;

  int count = 0;
  for (int i = 1; i <= n; ++i) {
    if (visited[i])
      continue;
    count++;
    cout << i << "\n";
  }
  if (count == 0)
    cout << "Connected\n";
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
