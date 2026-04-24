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

ll memo[18][145];
string limit_str;

ll solve_dp(int idx, bool tight, ll sum_sofar) {
  if (idx == limit_str.length()) {
    return sum_sofar;
  }

  if (!tight && memo[idx][sum_sofar] != -1) {
    return memo[idx][sum_sofar];
  }

  int max_digit = tight ? (limit_str[idx] - '0') : 9;
  ll total_sum = 0;
  for (int d = 0; d <= max_digit; ++d) {
    bool next_tight = tight && (d == max_digit);

    total_sum += solve_dp(idx + 1, next_tight, sum_sofar + d);
  }

  if (!tight) {
    memo[idx][sum_sofar] = total_sum;
  }
  return total_sum;
}

ll get_digit_sum(ll x) {
  if (x < 0)
    return 0;
  limit_str = to_string(x);

  while (limit_str.length() < 16) {
    limit_str = "0" + limit_str;
  }
  return solve_dp(0, true, 0);
}

void solve() {
  ll A, B;
  cin >> A >> B;

  ll ans = get_digit_sum(B) - get_digit_sum(A - 1);
  cout << ans << "\n";
}

int main() {
  fast_io();

  memset(memo, -1, sizeof(memo));

  int t = 1;
  cin >> t;

  while (t--) {
    solve();
  }

  return 0;
}
