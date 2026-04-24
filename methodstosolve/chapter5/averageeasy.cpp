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
template <class T> T read() {
  T v;
  std::cin >> v;
  return v;
}

void fast_io() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
}

void solve() {
  int N, M;
  cin >> N >> M;
  ll total_cs = 0, total_e = 0;
  vector<ll> cs(N);
  for (int i = 0; i < N; ++i) {
    cin >> cs[i];
    total_cs += cs[i];
  }
  for (int i = 0; i < M; ++i) {
    int val;
    cin >> val;
    total_e += val;
  }

  int count = 0;
  for (auto val : cs) {
    if (val * M > total_e && val * N < total_cs)
      count++;
  }
  cout << count << "\n";
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
