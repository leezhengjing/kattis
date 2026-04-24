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
template <class T> T read() {
  T v;
  std::cin >> v;
  return v;
}

void fast_io() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
}

void solve() {
  int ans[11];
  for (int i = 1; i <= 10; ++i) {
    int val = i * 7;
    // cout << val << " ";
    val %= 10;
    ans[val] = i;
  }
  // cout << "\n";

  int cur;

  cin >> cur;
  int initial = cur;
  cur %= 10;
  // for (auto val : ans) {
  //   cout << val << " ";
  // }

  int res = ans[cur];
  if (initial >= res * 7) {
    cout << ans[cur] << "\n";
  } else {
    cout << "-1\n";
  }
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
