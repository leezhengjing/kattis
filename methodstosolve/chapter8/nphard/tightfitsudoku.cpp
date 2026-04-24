#include <bits/stdc++.h>
// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/tree_policy.hpp>
using namespace std;
// using namespace __gnu_pbds;

typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
// typedef tuple<int, ll, ll> edge;
typedef tuple<int, ll, ll, ll> edge;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<vi> vvi;

#define LSOne(S) ((S) & -(S))
// int two_pow_p1 = LSOne(mask);
// int p1 = __builtin_ctz(two_pow_p1);
#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define sz(x) (int)(x).size()

const ll INF = 1e18;

int req1[36], req2[36], ans1[36], ans2[36];
int R[6], C[6], B[6];

void fast_io() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
}

inline void toggle(int r, int c, int b, int d) {
  R[r] ^= (1 << d);
  C[c] ^= (1 << d);
  B[b] ^= (1 << d);
}

inline bool is_valid(int r, int c, int b, int d) {
  return !((R[r] | C[c] | B[b]) & (1 << d));
}

bool dfs(int u) {
  if (u == 36)
    return true;

  int r = u / 6, c = u % 6, b = (r / 2) * 2 + c / 3;

  int s1 = req1[u] ? req1[u] : 1;
  int e1 = req1[u] ? req1[u] : (req2[u] == -1 ? 9 : 8);

  for (int d1 = s1; d1 <= e1; ++d1) {
    if (!is_valid(r, c, b, d1))
      continue;

    toggle(r, c, b, d1);
    ans1[u] = d1;

    if (req2[u] == -1) {
      if (dfs(u + 1))
        return true;
    } else {
      int s2 = req2[u] ? req2[u] : d1 + 1;
      int e2 = req2[u] ? req2[u] : 9;

      if (d1 < s2) {
        for (int d2 = s2; d2 <= e2; ++d2) {
          if (!is_valid(r, c, b, d2))
            continue;
          toggle(r, c, b, d2);
          ans2[u] = d2;
          if (dfs(u + 1))
            return true;
          toggle(r, c, b, d2);
        }
      }
    }

    toggle(r, c, b, d1);
  }
  return false;
}

void solve() {
  for (int i = 0; i < 36; ++i) {
    string s;
    cin >> s;
    int p = s.find('/');
    if (p == string::npos) {
      req1[i] = (s[0] == '-') ? 0 : s[0] - '0';
      req2[i] = -1;
    } else {
      req1[i] = (s[0] == '-') ? 0 : s[0] - '0';
      req2[i] = (s[p + 1] == '-') ? 0 : s[p + 1] - '0';
    }
  }
  dfs(0);
  for (int i = 0; i < 36; ++i) {
    if (req2[i] == -1)
      cout << ans1[i];
    else
      cout << ans1[i] << "/" << ans2[i];
    cout << ((i % 6 == 5) ? "\n" : " ");
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
