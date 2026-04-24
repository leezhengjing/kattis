#include <bits/stdc++.h>
// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/tree_policy.hpp>
using namespace std;
// using namespace __gnu_pbds;

typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<vi> vvi;

#define LSOne(S) ((S) & -(S))
// int two_pow_p1 = LSOne(mask);
// int p1 = __builtin_ctz(two_pow_p1);
#define REP(i, s, t) for (int i = (s); i < (t); ++i)

template <class T> T read() {
  T v;
  std::cin >> v;
  return v;
}

void fast_io() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
}

bool visited[10005];

vvi AL;
vi owed;

int dfs(int u) {
  if (visited[u]) {
    return 0;
  }

  visited[u] = true;
  int sum = owed[u];
  for (auto v : AL[u]) {
    sum += dfs(v);
  }
  return sum;
}

void solve() {
  int n, m;
  cin >> n >> m;
  AL.resize(n);
  owed.resize(n);
  for (int i = 0; i < n; ++i) {
    cin >> owed[i];
  }

  // find CC and calculate sum of CC == 0. if != 0 return IMPOSSIBLE

  for (int i = 0; i < m; ++i) {
    int u, v;
    cin >> u >> v;
    AL[u].push_back(v);
    AL[v].push_back(u);
  }

  for (int i = 0; i < n; ++i) {
    if (visited[i])
      continue;
    int curr = dfs(i);
    if (curr != 0) {
      cout << "IMPOSSIBLE\n";
      return;
    }
  }

  cout << "POSSIBLE\n";
  return;
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
