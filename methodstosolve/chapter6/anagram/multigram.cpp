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

bool check_multigram(const string &s, int n, int L) {
  vector<int> target_freq(26, 0);
  for (int i = 0; i < L; ++i) {
    target_freq[s[i] - 'a']++;
  }

  for (int i = L; i < n; i += L) {
    vector<int> chunk_freq(26, 0);

    for (int j = 0; j < L; ++j) {
      chunk_freq[s[i + j] - 'a']++;
    }

    if (chunk_freq != target_freq) {
      return false;
    }
  }

  return true;
}

void solve() {
  string s;
  cin >> s;

  int n = s.length();
  for (int L = 1; L <= n / 2; ++L) {
    if (n % L == 0) {
      if (check_multigram(s, n, L)) {
        cout << s.substr(0, L) << "\n";
        return;
      }
    }
  }
  cout << "-1\n";
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
