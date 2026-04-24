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
  int k, w;
  cin >> k >> w;

  vector<string> words(w);
  for (int i = 0; i < w; ++i) {
    cin >> words[i];
  }

  int res = k;
  for (int i = 1; i < w; ++i) {
    string &u = words[i - 1];
    string &v = words[i];
    int longest_ps = 0;
    for (int j = 0; j < k; ++j) {
      if (v.find(u.substr(j)) == 0) {
        // if (u.substr(j) == v.substr(0, k - j)) {

        longest_ps = k - j;
        break;
      }
    }

    res += k - longest_ps;
  }
  cout << res << "\n";
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
