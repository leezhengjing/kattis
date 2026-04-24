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
  ll N;
  cin >> N;

  for (ll k = 2; k * (k - 1) / 2 < N; ++k) {
    ll staircase = k * (k - 1) / 2;
    ll remainder = N - staircase;

    if (remainder % k == 0) {
      ll a = remainder / k;

      cout << N << " = ";
      for (ll i = 0; i < k; ++i) {
        cout << a + i;
        if (i < k - 1)
          cout << " + ";
      }
      cout << "\n";
      return;
    }
  }

  cout << "IMPOSSIBLE\n";
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
