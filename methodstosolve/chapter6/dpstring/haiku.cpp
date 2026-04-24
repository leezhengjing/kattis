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

unordered_set<string> syllables;

bool check_haiku_line(const string &line, int target_syllables) {
  int n = line.length();

  // dp[i][j] = true if prefix of length i can be formed with exactly j
  // syllables
  vector<vector<bool>> dp(n + 1, vector<bool>(target_syllables + 1, false));

  dp[0][0] = true;

  for (int i = 1; i <= n; ++i) {
    if (line[i - 1] == ' ') {
      for (int j = 0; j <= target_syllables; ++j) {
        dp[i][j] = dp[i - 1][j];
      }
    } else {
      for (int len = 1; len <= 7 && len <= i; ++len) {
        string sub = line.substr(i - len, len);

        if (syllables.count(sub)) {
          for (int j = 1; j <= target_syllables; ++j) {
            if (dp[i - len][j - 1]) {
              dp[i][j] = true;
            }
          }
        }
      }
    }
  }

  return dp[n][target_syllables];
}

void solve() {
  int s;
  cin >> s;

  for (int i = 0; i < s; ++i) {
    string syllable;
    cin >> syllable;
    syllables.insert(syllable);
  }

  string dummy;
  getline(cin, dummy);

  string line1, line2, line3;
  getline(cin, line1);
  getline(cin, line2);
  getline(cin, line3);

  if (check_haiku_line(line1, 5) && check_haiku_line(line2, 7) &&
      check_haiku_line(line3, 5))
    cout << "haiku\n";
  else
    cout << "come back next year\n";
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
