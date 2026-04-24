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
  string s;
  cin >> s;
  // ll res = 0;
  // for (char c : s) {
  //   int digit = c - '0';
  //   res = res * 2 + digit;
  // }
  // if (res == 0) {
  //   cout << "0\n";
  // } else {
  //
  //   string ans = "";
  //   while (res > 0) {
  //     ans += to_string(res % 8);
  //     res /= 8;
  //   }
  //   reverse(ans.begin(), ans.end());
  //   cout << ans << "\n";
  // }
  //
  while (s.length() % 3 != 0) {
    s = "0" + s;
  }

  string ans = "";
  for (int i = 0; i < s.length(); i += 3) {
    int val = 0;
    for (int j = 0; j < 3; ++j) {
      val = val * 2 + (s[i + j] - '0');
    }
    ans += to_string(val);
  }

  cout << ans << "\n";
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
