#include <bits/stdc++.h>
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
  vi e;
  void init(int N) { e = vi(N + 1, -1); }
  int get(int x) { return e[x] < 0 ? x : e[x] = get(e[x]); }
  int size(int x) { return -e[get(x)]; }
  int unite(int x, int y) {
    x = get(x), y = get(y);
    if (x == y)
      return 0;
    if (e[x] > e[y])
      swap(x, y);
    e[x] += e[y];
    e[y] = x;
    return 1;
  }
};

void solve() {
  int N;
  cin >> N;
  unordered_map<string, int> set;
  int id = 0;
  DSU dsu;
  dsu.init(N * 2);
  // 6 upper case or lowercase letters.. 26 * 2 = 52.. 52^ 6...
  // okay upper bound is 100 000 bridges/tunnels.. so 2*N
  for (int i = 0; i < N; ++i) {
    string a, b;
    cin >> a >> b;
    if (set.find(a) == set.end()) {
      set.insert({a, id++});
    }
    if (set.find(b) == set.end()) {
      set.insert({b, id++});
    }
    int a_idx = set.find(a)->second, b_idx = set.find(b)->second;
    dsu.unite(a_idx, b_idx);
    cout << dsu.size(a_idx) << "\n";
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
