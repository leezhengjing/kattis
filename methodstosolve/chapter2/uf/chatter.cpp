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
  void init(int n) { e = vi(n, -1); }
  int get(int x) { return (e[x] < 0 ? x : e[x] = get(e[x])); }
  int size(int x) { return -e[get(x)]; }
  map<int, int> sizes() {
    map<int, int> res;
    for (auto size : e) {
      if (size < 0) {
        auto iter = res.find(-size);
        if (iter == res.end()) {
          res.insert({-size, 1});
        } else {
          iter->second++;
        }
      }
    }
    return res;
  }
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

ll N, R, A, B, C;
void solve() {
  DSU dsu;
  dsu.init(N);
  ll ncc = N;
  for (int i = 0; i < N; ++i) {
    R = (R * A + B) % C;
    ll a = R % N;
    R = (R * A + B) % C;
    ll b = R % N;
    while (a == b) {
      R = (R * A + B) % C;
      a = R % N;
      R = (R * A + B) % C;
      b = R % N;
    }
    // cerr << "n: " << i << "\n";
    // cerr << a << " " << b << "\n";

    if (dsu.unite(a, b)) {
      ncc -= 1;
    }
  }
  cout << ncc << " ";

  map<int, int> size_freq = dsu.sizes();
  for (auto iter = size_freq.rbegin(); iter != size_freq.rend(); ++iter) {
    if (iter->second == 1) {
      cout << iter->first << " \n"[next(iter) == size_freq.rend()];
    } else {
      cout << iter->first << "x" << iter->second
           << " \n"[next(iter) == size_freq.rend()];
    }
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;

  while (cin >> N >> R >> A >> B >> C) {
    solve();
  }

  return 0;
}
