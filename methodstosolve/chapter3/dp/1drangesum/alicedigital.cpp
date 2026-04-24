#include <bits/stdc++.h>
// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/tree_policy.hpp>
using namespace std;
// using namespace __gnu_pbds;

typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<vi> vvi;

#define LSOne(S) ((S) & -(S))
// int two_pow_p1 = LSOne(mask);
// int p1 = __builtin_ctz(two_pow_p1);
#define REP(i, s, t) for (int i = (s); i < (t); ++i)

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
  // cin.ignore(numeric_limits<streamsize>::max(), '\n');
  int n, m;
  cin >> n >> m;

  vi dp(n + 1, 0);

  int prev_m = 0;

  int res = 0;
  for (int i = 1; i <= n; ++i) {
    int val;
    cin >> val;
    if (val < m) {
      dp[i] = 0;
      prev_m = 0;
      continue;
    }
    dp[i] += dp[i - 1];
    dp[i] += val;
    if (val == m) {
      dp[i] -= dp[prev_m];
      prev_m = i;
    }
    if (prev_m != 0)
      res = max(res, dp[i]);
  }

  cout << res << "\n";
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;

  while (t--) {
    // code here
    solve();
  }

  // reading input
  // read int: int n; cin >> n;
  // read line: string s; getline(cin, s);
  // read list/arr: vi arr(n); for(int i=0; i<n; ++i) cin >> arr[i];
  // eof reading: int n; while(cin >> n) { ... }

  return 0;
}
