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
  DSU dsu;
  dsu.init(500000);
  int res = 0;
  for (int i = 0; i < N; ++i) {
    int M;
    cin >> M;
    vi arr(M);
    map<int, int> root_freq;
    for (int j = 0; j < M; ++j) {
      cin >> arr[j];
      root_freq[dsu.get(arr[j])]++;
    }

    bool is_valid = true;
    for (auto val : arr) {
      if (root_freq[dsu.get(val)] != dsu.size(val)) {
        is_valid = false;
      }
    }
    if (is_valid) {
      for (int j = 0; j < M - 1; ++j) {
        dsu.unite(arr[j], arr[j + 1]);
      }
      res++;
    }
  }
  cout << res << "\n";
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
