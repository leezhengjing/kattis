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

void solve() {
  int N;
  cin >> N;
  for (int i = 0; i < N; ++i) {
    int idx;
    cin >> idx;
    ll p, q;
    char slash;
    cin >> p >> slash >> q;

    vector<char> path;

    while (p != 1 | q != 1) {
      if (p > q) {
        path.push_back('R');
        p -= q;
      } else {
        path.push_back('L');
        q -= p;
      }
    }

    ll res = 1;
    for (int i = path.size() - 1; i >= 0; --i) {
      if (path[i] == 'L') {
        res = res * 2;
      } else {
        res = 2 * res + 1;
      }
    }

    cout << idx << " " << res << "\n";
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
