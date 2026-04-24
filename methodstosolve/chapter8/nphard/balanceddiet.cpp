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
template <class T> T read() {
  T v;
  std::cin >> v;
  return v;
}

void fast_io() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
}

const int MAX = 12001;
void solve() {
  int n;

  while (cin >> n && n != 0) {
    vi arr(n);
    int total = 0;
    for (int i = 0; i < n; ++i) {
      cin >> arr[i];
      total += arr[i];
    }

    bitset<MAX> dp;
    dp[0] = 1;

    for (auto can : arr) {
      dp |= (dp << can);
    }

    int target = total / 2;

    int meal1 = 0, meal2 = 0;

    for (int i = target; i >= 0; --i) {
      if (dp[i]) {
        meal2 = i;
        break;
      }
    }

    meal1 = total - meal2;

    cout << meal1 << " " << meal2 << "\n";
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
