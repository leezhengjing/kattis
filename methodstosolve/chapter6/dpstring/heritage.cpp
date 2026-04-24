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

void solve() {
  int n;
  string target;

  cin >> n >> target;

  unordered_map<string, ll> dict;
  for (int i = 0; i < n; ++i) {
    string word;
    ll m;
    cin >> word >> m;
    dict[word] = m; // (dict[word] + m) % MOD;
  }

  int L = target.length();
  vll dp(L + 1, 0);

  dp[0] = 1;

  for (int i = 1; i <= L; ++i) {
    for (int len = 1; len <= i; ++len) {
      if (dp[i - len] == 0)
        continue;

      string sub = target.substr(i - len, len);

      auto it = dict.find(sub);
      if (it != dict.end()) {
        dp[i] = (dp[i] + dp[i - len] * it->second) % MOD;
      }
    }
  }

  cout << dp[L] << "\n";
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
