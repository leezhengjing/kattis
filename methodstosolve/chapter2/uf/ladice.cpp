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

void fast_io() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
}

struct DSU {
  vi e;
  vi free;

  void init(int n) {
    e = vi(n, -1);
    free = vi(n, 1);
  }
  int get(int x) { return (e[x] < 0 ? x : e[x] = get(e[x])); }
  int unite(int x, int y) {
    x = get(x), y = get(y);
    if (x != y) {
      if (e[x] > e[y])
        swap(x, y);
      e[x] += e[y];
      e[y] = x;
      free[x] += free[y];
    }

    if (free[x] > 0) {
      free[x]--;
      return 1;
    }
    return 0;
  }
};

void solve() {
  int N, L;
  cin >> N >> L;
  DSU dsu;
  dsu.init(L + 1);
  for (int i = 0; i < N; ++i) {
    int a, b;
    cin >> a >> b;

    if (dsu.unite(a, b)) {
      cout << "LADICA\n";
    } else {
      cout << "SMECE\n";
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
