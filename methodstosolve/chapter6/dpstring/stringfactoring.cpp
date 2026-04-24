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
const int MOD = 1e9 + 7;

void fast_io() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
}

bool is_period(const string &s, int i, int j, int len) {
  for (int k = i + len; k <= j; ++k) {
    if (s[k] != s[k - len])
      return false;
  }
  return true;
}

void solve() {
  string s;
  cin >> s;

  int n = s.length();

  vvi dp(n, vi(n, 0));

  for (int L = 1; L <= n; ++L) {
    for (int i = 0; i <= n - L; ++i) {
      int j = i + L - 1;

      if (L == 1) {
        dp[i][j] = 1;
        continue;
      }

      dp[i][j] = L;

      for (int k = i; k < j; ++k) {
        dp[i][j] = min(dp[i][j], dp[i][k] + dp[k + 1][j]);
      }

      for (int len = 1; len <= L / 2; ++len) {
        if (L % len == 0) {
          if (is_period(s, i, j, len)) {
            dp[i][j] = min(dp[i][j], dp[i][i + len - 1]);
          }
        }
      }
    }
  }

  cout << dp[0][n - 1] << "\n";
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
