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
  cin >> n;

  vector<long long> h(n), a(n), c(n);
  long long max_h = 0;

  // Read Healths and find the maximum health
  for (int i = 0; i < n; ++i) {
    cin >> h[i];
    max_h = max(max_h, h[i]);
  }

  // Read Attacks and Costs
  for (int i = 0; i < n; ++i)
    cin >> a[i];
  for (int i = 0; i < n; ++i)
    cin >> c[i];

  // dp[s] represents the max score with exactly 's' attack power coming from
  // the right
  const long long INF =
      1e18; // Use a very large negative number for impossible states
  vector<long long> dp(max_h + 1, -INF);

  // Base case: before processing any elements (at the far right),
  // a sum of 0 has a score of 0. All other sums are impossible.
  dp[0] = 0;

  // Process from right to left
  for (int i = n - 1; i >= 0; --i) {
    // Create a temporary DP array for the current step
    vector<long long> next_dp(max_h + 1, -INF);

    for (int s = 0; s <= max_h; ++s) {
      if (dp[s] == -INF)
        continue; // Skip unreachable states

      // Option 1: Do NOT fire Piplup i
      next_dp[s] = max(next_dp[s], dp[s]);

      // Option 2: Fire Piplup i
      long long next_s = min(max_h, s + a[i]);
      next_dp[next_s] = max(next_dp[next_s], dp[s] - c[i]);
    }

    // Add the damage dealt to the i-th Chimchar for all valid states
    for (int s = 0; s <= max_h; ++s) {
      if (next_dp[s] != -INF) {
        next_dp[s] += min((long long)s, h[i]);
      }
    }

    // Move to the next step
    dp = next_dp;
  }

  // The answer is the maximum score across all possible ending attack sums
  long long ans = -INF;
  for (int s = 0; s <= max_h; ++s) {
    ans = max(ans, dp[s]);
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
