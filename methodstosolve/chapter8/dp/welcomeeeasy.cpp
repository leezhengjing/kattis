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

string check = "welcome to code jam";
int MOD = 1e5;
int dp[20];
int t = 1;

int t_copy = 1;
void solve() {
  memset(dp, 0, sizeof(dp));
  dp[0] = 1;
  string s;

  getline(cin, s);

  for (auto c : s) {
    for (int i = check.size() - 1; i >= 0; i--) {
      if (c == check[i]) {
        dp[i + 1] = (dp[i + 1] + dp[i]) % MOD;
      }
    }
  }

  int res = dp[19];
  cout << "Case #" << t_copy - t << ": " << setfill('0') << setw(4) << dp[19]
       << "\n";
  // if (res == 0)
  //   cout << "0000\n";
  // else if (res / 10 == 0)
  //   cout << "000" << res << "\n";
  // else if (res / 100 == 0)
  //   cout << "00" << res << "\n";
  // else if (res / 1000 == 0)
  //   cout << "0" << res << "\n";
  // else
  //   cout << res << "\n";
}

int main() {
  fast_io();

  cin >> t;
  t_copy = t;
  cin.ignore();

  while (t--) {
    solve();
  }

  return 0;
}
