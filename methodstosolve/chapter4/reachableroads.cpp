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

vvi AL;
int n;
bool visited[1005];

void dfs(int u) {
  if (visited[u])
    return;

  visited[u] = true;
  for (auto v : AL[u]) {
    if (visited[v])
      continue;
    dfs(v);
  }
}

void solve() {
  int m, r;
  cin >> m >> r;
  AL.assign(m, vi());
  memset(visited, false, sizeof(visited));

  for (int i = 0; i < r; ++i) {
    int u, v;
    cin >> u >> v;
    AL[u].push_back(v);
    AL[v].push_back(u);
  }
  int numCC = 0;
  for (int i = 0; i < m; ++i) {
    if (visited[i])
      continue;
    dfs(i);
    numCC++;
  }

  cout << numCC - 1 << "\n";
}

int main() {
  fast_io();

  cin >> n;
  int t = n;

  while (t--) {
    solve();
  }

  return 0;
}
