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

const int INF = 1e9;
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
  vi hotdogs(n);
  int total_hotdogs = 0;
  for (int i = 0; i < n; ++i) {
    cin >> hotdogs[i];
    total_hotdogs += hotdogs[i];
  }

  int m;
  cin >> m;
  vi buns(m);
  int total_buns = 0;
  for (int i = 0; i < m; ++i) {
    cin >> buns[i];
    total_buns += buns[i];
  }

  vector<vector<int>> dp1(n + 1, vector<int>(total_hotdogs + 1, INF));
  vector<vector<int>> dp2(m + 1, vector<int>(total_buns + 1, INF));
  dp1[0][0] = 0;
  dp2[0][0] = 0;

  for (int i = 1; i <= n; ++i) {
    for (int w = 0; w <= total_hotdogs; ++w) {
      if (w == 0)
        dp1[i][w] = 0;
      else if (w - hotdogs[i - 1] < 0) {
        dp1[i][w] = min(dp1[i][w], dp1[i - 1][w]);
      } else {
        dp1[i][w] = min(dp1[i][w], dp1[i - 1][w]);
        if (dp1[i - 1][w - hotdogs[i - 1]] != INF)
          dp1[i][w] = min(dp1[i][w], dp1[i - 1][w - hotdogs[i - 1]] + 1);
      }
    }
  }

  for (int i = 1; i <= m; ++i) {
    for (int w = 0; w <= total_buns; ++w) {
      if (w == 0)
        dp2[i][w] = 0;
      else if (w - buns[i - 1] < 0) {
        dp2[i][w] = min(dp2[i][w], dp2[i - 1][w]);
      } else {
        dp2[i][w] = min(dp2[i][w], dp2[i - 1][w]);
        if (dp2[i - 1][w - buns[i - 1]] != INF)
          dp2[i][w] = min(dp2[i][w], dp2[i - 1][w - buns[i - 1]] + 1);
      }
    }
  }

  // for (int i = 0; i <= min(n, m); ++i) {
  //   for (int w = 1; w <= min(total_hotdogs, total_buns); ++w) {
  //     if (dp1[i][w] > 0 && dp2[i][w] > 0) {
  //       cout << dp1[i][w] << "\n";
  //       cout << dp2[i][w] << "\n";
  //       cout << i << "\n";
  //       return;
  //     }
  //   }
  // }

  int res = INF;
  for (int w = 1; w <= min(total_hotdogs, total_buns); ++w) {
    if (dp1[n][w] != INF && dp2[m][w] != INF) {
      res = min(res, dp1[n][w] + dp2[m][w]);
    }
  }

  if (res == INF) {
    cout << "impossible\n";
  } else {
    cout << res << "\n";
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
