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
  string s;
  getline(cin, s);

  string clean_s = "";

  for (char c : s) {
    if (isalpha(c))
      clean_s += tolower(c);
  }

  int n = clean_s.length();
  bool is_anti = true;
  for (int i = 0; i < n; ++i) {
    if (i >= 1 && clean_s[i] == clean_s[i - 1]) {
      is_anti = false;
      break;
    }
    if (i >= 2 && clean_s[i] == clean_s[i - 2]) {
      is_anti = false;
      break;
    }
  }
  if (is_anti)
    cout << "Anti-palindrome\n";
  else
    cout << "Palindrome\n";
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
