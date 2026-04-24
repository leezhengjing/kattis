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

ll memo[16][145][2][2];
string A_str, B_str;

void fast_io() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
}

ll solve_dp(int idx, int remain, bool tight_a, bool tight_b) {
  if (remain < 0)
    return 0;

  if (idx == 16)
    return remain == 0;

  if (memo[idx][remain][tight_a][tight_b] != -1) {
    return memo[idx][remain][tight_a][tight_b];
  }

  int min_d = tight_a ? A_str[idx] - '0' : 0;
  int max_d = tight_b ? B_str[idx] - '0' : 9;

  ll ways = 0;

  for (int d = min_d; d <= max_d; ++d) {
    bool next_tight_a = tight_a && (d == min_d);
    bool next_tight_b = tight_b && (d == max_d);

    ways += solve_dp(idx + 1, remain - d, next_tight_a, next_tight_b);
  }

  return memo[idx][remain][tight_a][tight_b] = ways;
}

void solve() {
  ll A, B;
  int S;
  cin >> A >> B >> S;

  A_str = to_string(A);
  B_str = to_string(B);

  while (A_str.length() < 16)
    A_str = "0" + A_str;
  while (B_str.length() < 16)
    B_str = "0" + B_str;

  memset(memo, -1, sizeof(memo));

  ll count = solve_dp(0, S, true, true);
  cout << count << "\n";

  string min_val = "";

  int curr = S;
  bool tight_a = true, tight_b = true;

  for (int i = 0; i < 16; ++i) {
    int min_d = tight_a ? A_str[i] - '0' : 0;
    int max_d = tight_b ? B_str[i] - '0' : 9;

    for (int d = min_d; d <= max_d; ++d) {
      bool next_tight_a = tight_a && (d == min_d);
      bool next_tight_b = tight_b && (d == max_d);

      if (solve_dp(i + 1, curr - d, next_tight_a, next_tight_b) > 0) {
        min_val += to_string(d);
        curr -= d;
        tight_a = next_tight_a;
        tight_b = next_tight_b;
        break;
      }
    }
  }
  cout << stoll(min_val) << "\n";
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
