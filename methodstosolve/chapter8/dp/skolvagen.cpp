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
const int INT_INF = 1e9;
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
  string s;
  cin >> s;

  int n = s.size();

  vvi dp(2, vi(n + 1, INT_INF));
  dp[0][0] = 0;
  dp[1][0] = 1;

  for (int i = 1; i <= n; ++i) {
    if (s[i - 1] == 'N') {
      dp[0][i] = dp[0][i - 1] + 1;
      dp[1][i] = dp[1][i - 1];
    } else if (s[i - 1] == 'S') {
      dp[0][i] = dp[0][i - 1];
      dp[1][i] = dp[1][i - 1] + 1;
    } else if (s[i - 1] == 'B') {
      dp[0][i] = dp[0][i - 1] + 1;
      dp[1][i] = dp[1][i - 1] + 1;
    }
    dp[0][i] = min(dp[0][i], dp[1][i] + 1);
    dp[1][i] = min(dp[1][i], dp[0][i] + 1);
  }
  cout << dp[0][n] << "\n";
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
