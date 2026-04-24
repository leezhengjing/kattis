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
  string s;
  getline(cin, s);

  vector<bool> seen(26, false);
  int unique_letters = 0;

  for (char c : s) {
    if (isalpha(c)) {
      int idx = tolower(c) - 'a';

      if (!seen[idx]) {
        seen[idx] = true;
        unique_letters++;
      }
    }
  }

  if (unique_letters == 26) {
    cout << "pangram\n";
  } else {
    cout << "missing ";
    for (int i = 0; i < 26; ++i) {
      if (!seen[i]) {
        cout << (char)('a' + i);
      }
    }
    cout << "\n";
  }
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  cin.ignore();

  while (t--) {
    solve();
  }

  return 0;
}
