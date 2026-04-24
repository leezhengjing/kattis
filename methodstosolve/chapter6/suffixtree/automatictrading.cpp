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
const ll MOD = 1e9 + 7;
const ll BASE = 131;

void fast_io() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
}

vll h, p;

void build_hash(const string &s) {
  int n = s.length();
  h.assign(n + 1, 0);
  p.assign(n + 1, 1);

  for (int i = 0; i < n; ++i) {
    h[i + 1] = (h[i] * BASE + s[i]) % MOD;
    p[i + 1] = (p[i] * BASE) % MOD;
  }
}

ll get_hash(int L, int R) {
  ll hash_val = (h[R + 1] - h[L] * p[R - L + 1]) % MOD;
  if (hash_val < 0)
    hash_val += MOD;
  return hash_val;
}

void solve() {
  string s;
  cin >> s;

  build_hash(s);

  int q;
  cin >> q;
  int n = s.length();
  for (int i = 0; i < q; ++i) {
    int a, b;
    cin >> a >> b;

    if (a == b) {
      cout << n - a << "\n";
      continue;
    }

    int low = 0, high = n - max(a, b);
    int ans = 0;

    while (low <= high) {
      int mid = low + (high - low) / 2;
      if (mid == 0) {
        low = mid + 1;
        continue;
      }
      if (get_hash(a, a + mid - 1) == get_hash(b, b + mid - 1)) {
        ans = mid;
        low = mid + 1;
      } else {
        high = mid - 1;
      }
    }
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
