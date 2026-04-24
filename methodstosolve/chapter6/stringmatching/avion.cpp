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

int tc = 0;

void solve() {
  int count = 0;
  string s;
  vi res;
  while (cin >> s) {
    ++tc;
    if (s.find("FBI") != string::npos) {
      count++;
      res.push_back(tc);
    }
  }

  if (count == 0)
    cout << "HE GOT AWAY!\n";
  else {
    for (int i = 0; i < count; ++i) {
      cout << res[i] << " \n"[i == count - 1];
    }
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;

  solve();

  return 0;
}
