#include <bits/stdc++.h>
#include <csetjmp>
// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/tree_policy.hpp>
using namespace std;
// using namespace __gnu_pbds;

typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef tuple<int, ll, ll> edge; // For MaxFlow
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<vi> vvi;

#define LSOne(S) ((S) & -(S))
// int two_pow_p1 = LSOne(mask);
// int p1 = __builtin_ctz(two_pow_p1);
#define REP(i, s, t) for (int i = (s); i < (t); ++i)

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

struct DSU {
  vi e, mapping;
  vll total;
  int id_counter;
  void init(int n, int m) {
    e.assign(n + m + 1, -1);
    total.assign(n + m + 1, 0);
    mapping.resize(n + 1);

    for (int i = 1; i <= n; ++i) {
      mapping[i] = i;
      total[i] += i;
    }
    id_counter = n + 1;
  }

  int get(int x) { return e[x] < 0 ? x : e[x] = get(e[x]); }
  int size(int x) { return -e[get(mapping[x])]; }
  ll sum(int x) { return total[get(mapping[x])]; }
  void unite(int x, int y) {
    // x = get(x), y = get(y);
    // if (x == y)
    //   return 0;
    // if (e[x] > e[y])
    //   swap(x, y);
    // e[x] += e[y];
    // total[x] += total[y];
    // e[y] = x;
    // return 1;
    int root_x = get(mapping[x]), root_y = get(mapping[y]);
    if (root_x != root_y) {
      e[root_x] += e[root_y];
      total[root_x] += total[root_y];
      e[root_y] = root_x;
    }
  }
  void move(int x, int y) {
    int root_x = get(mapping[x]), root_y = get(mapping[y]);
    if (root_x == root_y)
      return;

    e[root_x]++;
    total[root_x] -= x;

    int new_id = id_counter++;
    mapping[x] = new_id;

    e[new_id] = -1;
    total[new_id] = x;

    int root_new = get(new_id);
    e[root_y] += e[root_new];
    total[root_y] += total[root_new];
    e[root_new] = root_y;
  }
};

int n, m;
void solve() {
  DSU dsu;
  dsu.init(n, m);
  for (int i = 0; i < m; ++i) {
    int type;
    cin >> type;
    if (type == 3) {
      int p;
      cin >> p;
      cout << dsu.size(p) << " " << dsu.sum(p) << "\n";
    } else if (type == 2) {
      int p, q;
      cin >> p >> q;
      dsu.move(p, q);
    } else if (type == 1) {
      int p, q;
      cin >> p >> q;
      dsu.unite(p, q);
    }
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;

  while (cin >> n >> m) {
    solve();
  }

  return 0;
}
