#include <bits/stdc++.h>
// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/tree_policy.hpp>
using namespace std;
// using namespace __gnu_pbds;

typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef tuple<int, ll, ll> edge; // For MaxFlow
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<vi> vvi;

#define LSOne(S) ((S) & -(S))
// int two_pow_p1 = LSOne(mask);
// int p1 = __builtin_ctz(two_pow_p1);
#define REP(i, s, t) for (int i = (s); i < (t); ++i)

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
  int n;
  cin >> n;
  vi arr(n);
  for (int i = 0; i < n; ++i) {
    cin >> arr[i];
  }

  vi lis(n, 1), lds(n, 1);

  for (int i = n - 1; i >= 0; --i) {
    for (int j = i + 1; j < n; ++j) {
      if (arr[j] > arr[i]) {
        lis[i] = max(lis[i], 1 + lis[j]);
      }
      if (arr[j] < arr[i]) {
        lds[i] = max(lds[i], 1 + lds[j]);
      }
    }
  }

  int res = 0;
  for (int i = 0; i < n; ++i) {
    res = max(lis[i] + lds[i] - 1, res);
  }
  cout << res << "\n";
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
