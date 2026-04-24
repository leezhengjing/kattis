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

ll memo[20][10][2][2];
string limit_str;

bool is_hill(const string &s) {
  int phase = 0;
  for (int i = 1; i < s.length(); ++i) {
    if (phase == 0) {
      if (s[i] < s[i - 1])
        phase = 1;
    } else {
      if (s[i] > s[i - 1])
        return false;
    }
  }
  return true;
}
ll solve_dp(int idx, int prev_digit, int phase, bool tight, bool is_lz) {
  if (idx == limit_str.length())
    return 1;

  if (!tight && memo[idx][prev_digit][phase][is_lz] != -1) {
    return memo[idx][prev_digit][phase][is_lz];
  }

  int max_d = tight ? (limit_str[idx] - '0') : 9;
  ll ways = 0;

  for (int d = 0; d <= max_d; ++d) {
    bool next_tight = tight && (d == max_d);
    bool next_lz = is_lz && (d == 0);

    if (is_lz) {
      ways += solve_dp(idx + 1, d, 0, next_tight, next_lz);
    } else {
      if (phase == 0) {
        if (d >= prev_digit) {
          ways += solve_dp(idx + 1, d, 0, next_tight, next_lz);
        } else {
          ways += solve_dp(idx + 1, d, 1, next_tight, next_lz);
        }
      } else if (phase == 1) {
        if (d <= prev_digit) {
          ways += solve_dp(idx + 1, d, 1, next_tight, next_lz);
        }
      }
    }
  }

  if (!tight)
    memo[idx][prev_digit][phase][is_lz] = ways;

  return ways;
}

void solve() {
  cin >> limit_str;
  if (!is_hill(limit_str)) {
    cout << -1 << "\n";
    return;
  }

  memset(memo, -1, sizeof(memo));

  ll total = solve_dp(0, 0, 0, true, true);

  cout << total - 1 << "\n";
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
