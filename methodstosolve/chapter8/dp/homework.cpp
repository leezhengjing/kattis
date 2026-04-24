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

void solve() {
  string s0, s1, s2;
  cin >> s0 >> s1 >> s2;

  int n = s1.size();
  int m = s2.size();

  vector<vector<bool>> dp(n + 1, vector<bool>(m + 1, false));

  dp[0][0] = true;

  for (int i = 0; i <= n; ++i) {
    for (int j = 0; j <= m; ++j) {

      if (i > 0 && s1[i - 1] == s0[i + j - 1] && dp[i - 1][j]) {
        dp[i][j] = true;
      }

      if (j > 0 && s2[j - 1] == s0[i + j - 1] && dp[i][j - 1]) {
        dp[i][j] = true;
      }
    }
  }

  if (dp[n][m])
    cout << "yes\n";
  else
    cout << "no\n";
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
