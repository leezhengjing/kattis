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
  int b;
  string p, m;
  while (cin >> b && b != 0) {
    cin >> p >> m;
    int n = p.size();

    ll res = 0;
    int mod = 0;
    for (char c : m) {
      int digit = c - '0';
      mod = mod * b + digit;
    }

    for (char c : p) {
      int digit = c - '0';
      res = res * b + digit;
      res %= mod;
    }

    if (res == 0) {
      cout << "0\n";
    } else {
      string ans = "";
      while (res > 0) {
        ans += to_string(res % b);
        res /= b;
      }
      reverse(ans.begin(), ans.end());
      cout << ans << "\n";
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
