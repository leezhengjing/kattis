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
  int L, S;
  cin >> L >> S;

  string ans(L, '?');
  bool possible = true;

  for (int k = 0; k < S; ++k) {
    int p;
    string s;
    cin >> p >> s;

    if (!possible)
      continue;

    int star_pos = s.find('*');

    if (star_pos == string::npos) {
      for (int i = 0; i < s.length(); ++i) {
        int idx = p - 1 + i;
        if (ans[idx] == '?')
          ans[idx] = s[i];
        else if (ans[idx] != s[i])
          possible = false;
      }
    } else {
      int lenA = star_pos;
      int lenB = s.length() - 1 - star_pos;

      if (lenA + lenB > L - p + 1) {
        possible = false;
      } else {
        for (int i = 0; i < lenA; ++i) {
          int idx = p - 1 + i;
          if (ans[idx] == '?')
            ans[idx] = s[i];
          else if (ans[idx] != s[i])
            possible = false;
        }

        for (int i = 0; i < lenB; ++i) {
          int idx = L - lenB + i;
          if (ans[idx] == '?')
            ans[idx] = s[star_pos + 1 + i];
          else if (ans[idx] != s[star_pos + 1 + i])
            possible = false;
        }
      }
    }
  }

  if (possible) {
    for (char c : ans) {
      if (c == '?') {
        possible = false;
        break;
      }
    }
  }
  if (possible)
    cout << ans << "\n";
  else
    cout << "IMPOSSIBLE\n";
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
