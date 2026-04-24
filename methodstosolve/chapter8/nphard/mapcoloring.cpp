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

int N;
vvi AL;
vi color;

bool dfs(int u, int max_colors) {
  if (u == N)
    return true;

  for (int c = 1; c <= max_colors; ++c) {
    bool is_safe = true;

    for (int v : AL[u]) {
      if (color[v] == c) {
        is_safe = false;
        break;
      }
    }

    if (is_safe) {
      color[u] = c;
      if (dfs(u + 1, max_colors))
        return true;
      color[u] = 0;
    }
  }

  return false;
}

void solve() {
  int B;
  cin >> N >> B;
  color.assign(N, 0);
  AL.assign(N, vi());

  for (int i = 0; i < B; ++i) {
    int u, v;
    cin >> u >> v;
    AL[u].push_back(v);
    AL[v].push_back(u);
  }

  for (int k = 1; k <= 4; ++k) {
    fill(color.begin(), color.end(), 0);
    if (dfs(0, k)) {
      cout << k << "\n";
      return;
    }
  }
  cout << "many\n";
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;

  while (t--) {
    solve();
  }

  return 0;
}
