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

bool isMatch(const string &s, const string &p) {
  int m = s.length();
  int n = p.length();

  vector<vector<bool>> dp(n + 1, vector<bool>(m + 1, false));

  dp[0][0] = true;

  for (int i = 1; i <= n; ++i) {
    if (p[i - 1] == '*') {
      dp[i][0] = dp[i - 1][0];
      ;
    }
  }

  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= m; ++j) {
      if (p[i - 1] == '*') {
        dp[i][j] = dp[i - 1][j] | dp[i][j - 1];
      } else if (p[i - 1] == s[j - 1]) {
        dp[i][j] = dp[i - 1][j - 1];
      }
    }
  }

  return dp[n][m];
}

void solve() {
  string pattern;
  cin >> pattern;

  int n;
  cin >> n;

  while (n--) {
    string filename;
    cin >> filename;
    if (isMatch(filename, pattern)) {
      cout << filename << "\n";
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
