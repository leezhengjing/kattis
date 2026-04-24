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

unordered_set<string> elements = {
    "h",  "he", "li", "be", "b",  "c",  "n",  "o",  "f",  "ne", "na", "mg",
    "al", "si", "p",  "s",  "cl", "ar", "k",  "ca", "sc", "ti", "v",  "cr",
    "mn", "fe", "co", "ni", "cu", "zn", "ga", "ge", "as", "se", "br", "kr",
    "rb", "sr", "y",  "zr", "nb", "mo", "tc", "ru", "rh", "pd", "ag", "cd",
    "in", "sn", "sb", "te", "i",  "xe", "cs", "ba", "hf", "ta", "w",  "re",
    "os", "ir", "pt", "au", "hg", "tl", "pb", "bi", "po", "at", "rn", "fr",
    "ra", "rf", "db", "sg", "bh", "hs", "mt", "ds", "rg", "cn", "fl", "lv",
    "la", "ce", "pr", "nd", "pm", "sm", "eu", "gd", "tb", "dy", "ho", "er",
    "tm", "yb", "lu", "ac", "th", "pa", "u",  "np", "pu", "am", "cm", "bk",
    "cf", "es", "fm", "md", "no", "lr"};

void solve() {
  string s;
  cin >> s;

  int n = s.length();
  vector<bool> dp(n + 1, false);

  dp[0] = true;

  for (int i = 1; i <= n; ++i) {
    if (dp[i - 1] && elements.count(s.substr(i - 1, 1)))
      dp[i] = true;
    else if (i >= 2 && dp[i - 2] && elements.count(s.substr(i - 2, 2)))
      dp[i] = true;
  }

  if (dp[n])
    cout << "YES\n";
  else
    cout << "NO\n";
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;

  while (t--) {
    solve();
  }

  return 0;
}
