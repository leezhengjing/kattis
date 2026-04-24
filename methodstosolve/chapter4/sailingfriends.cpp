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

void solve() {
  int n, b, m;
  cin >> n >> b >> m;
  set<int> boats;
  for (int i = 0; i < b; ++i) {
    int val;
    cin >> val;
    boats.emplace(val);
  }

  vvi AL(n + 1);
  for (int i = 0; i < m; ++i) {
    int u, v;
    cin >> u >> v;

    AL[u].push_back(v);
    AL[v].push_back(u);
  }

  int numCC = 0;
  int numCCwboat = 0;
  vector<bool> visited(n + 1, false);

  for (int i = 1; i <= n; ++i) {
    if (visited[i])
      continue;
    queue<int> q;
    q.push(i);
    visited[i] = true;
    bool has_boat = boats.find(i) != boats.end();

    while (!q.empty()) {
      int u = q.front();
      q.pop();
      for (auto v : AL[u]) {
        if (visited[v])
          continue;
        visited[v] = true;
        q.push(v);
        has_boat |= boats.find(v) != boats.end();
      }
    }

    numCC++;
    if (has_boat)
      numCCwboat++;
  }

  cout << numCC - numCCwboat << "\n";
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
