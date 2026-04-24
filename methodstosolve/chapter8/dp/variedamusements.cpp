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
const int MOD = 1e9 + 7;
template <class T> T read() {
  T v;
  std::cin >> v;
  return v;
}

void fast_io() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
}

// a = 1, b = 2, c= 3, n=  5;
// lets say we want to build sequence of n = 1;
// 3 options: a, b, c
// n = 2:
// build on this,
// we can do ab, ac, ba, bc, ca, cb == 3 * 2 = 6
// n = 3;
// abc acb, bab, bac, bca, bcb, cac, cab, cba, cbc = 10
// n = 4;
// abcb acbc babc bacb bcab bcac bcba bcbc cacb cabc cbac cbab cbca cbcb = 14?
//

ll dp[55][3];

void solve() {
  int n, a, b, c;
  cin >> n >> a >> b >> c;

  dp[1][0] = a;
  dp[1][1] = b;
  dp[1][2] = c;
  for (int i = 2; i <= n; ++i) {
    dp[i][0] = ((dp[i - 1][1] * a) % MOD + (dp[i - 1][2] * a) % MOD) % MOD;
    dp[i][1] = ((dp[i - 1][0] * b) % MOD + (dp[i - 1][2] * b) % MOD) % MOD;
    dp[i][2] = ((dp[i - 1][0] * c) % MOD + (dp[i - 1][1] * c) % MOD) % MOD;
  }

  cout << (dp[n][0] + dp[n][1] + dp[n][2]) % MOD << "\n";
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
