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

void solve() {
  int base;
  cin >> base;

  unordered_map<string, int> alien_digits;
  for (int i = 0; i < base; ++i) {
    string digits_str;
    cin >> digits_str;
    alien_digits[digits_str] = i;
  }

  string alien_number;
  cin >> alien_number;

  ll ans = 0;
  string curr_chunk = "";
  for (char c : alien_number) {
    curr_chunk += c;

    if (alien_digits.count(curr_chunk)) {
      int digit_val = alien_digits[curr_chunk];

      ans = ans * base + digit_val;

      curr_chunk = "";
    }
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
