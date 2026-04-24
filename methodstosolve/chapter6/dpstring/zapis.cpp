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
const ll MOD = 1e5;

void fast_io() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
}

ll memo[205][205];
string s;

int get_match_ways(char a, char b) {
  if (a == '?' && b == '?')
    return 3;

  if (a == '?' && (b == ')' || b == ']' || b == '}'))
    return 1;

  if ((a == '(' || a == '[' || a == '{') && b == '?')
    return 1;

  if (a == '(' && b == ')')
    return 1;
  if (a == '{' && b == '}')
    return 1;
  if (a == '[' && b == ']')
    return 1;

  return 0;
}

ll solve_dp(int i, int j) {
  if (i > j)
    return 1;

  if (memo[i][j] != -1)
    return memo[i][j];

  ll total_ways = 0;

  for (int k = i + 1; k <= j; k += 2) {
    ll match_ways = get_match_ways(s[i], s[k]);

    if (match_ways > 0) {
      ll ways = match_ways * solve_dp(i + 1, k - 1) * solve_dp(k + 1, j);

      total_ways += ways;

      if (total_ways >= MOD)
        total_ways = (total_ways % MOD) + MOD;
    }
  }
  return memo[i][j] = total_ways;
}

void solve() {
  int n;
  cin >> n >> s;

  memset(memo, -1, sizeof(memo));

  ll ans = solve_dp(0, n - 1);

  if (ans >= MOD) {
    cout << setfill('0') << setw(5) << (ans % MOD) << "\n";
  } else {
    cout << ans << "\n";
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
