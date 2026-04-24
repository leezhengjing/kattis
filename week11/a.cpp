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

void fast_io() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
}

void solve() {
  ll X, Y, N;
  double P;

  while (cin >> X >> Y >> N >> P && (X != 0 || Y != 0 || N != 0 || P != 0)) {
    double r = P / 1200.0;
    ll M = N * 12;

    if (r == 0.0) {
      if (X <= (__int128)Y * M) {
        cout << "YES\n";
      } else {
        cout << "NO\n";
      }
      continue;
    }

    if (X * r >= Y) {
      cout << "NO\n";
      continue;
    }

    double v = pow(1.0 + r, M);
    double final_debt = X * v - Y * (v - 1.0) / r;

    if (final_debt <= 1e-7) {
      cout << "YES\n";
    } else {
      cout << "NO\n";
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
