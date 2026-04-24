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

vvi AL;
vi t_entry, t_exit;
int timer = 0;

void fast_io() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
}

void dfs(int u) {
  t_entry[u] = ++timer;
  for (int neighbor : AL[u]) {
    dfs(neighbor);
  }
  t_exit[u] = ++timer;
}

bool is_parent(int u, int v) {
  return t_entry[u] < t_entry[v] && t_exit[u] > t_exit[v];
}

void solve() {
  int N, M;
  cin >> N >> M;

  AL.assign(N + 1, vi());
  t_entry.assign(N + 1, 0);
  t_exit.assign(N + 1, 0);

  for (int i = 2; i <= N; ++i) {
    int manager;
    cin >> manager;
    AL[manager].push_back(i);
  }
  dfs(1);

  for (int i = 0; i < M; ++i) {
    int v, u;
    cin >> v >> u;

    if (is_parent(u, v)) {
      cout << "No\n";
    } else {
      cout << "Yes\n";
    }
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
