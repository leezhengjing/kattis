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

int C, n;
void solve() {
  vi values(n);
  vi weights(n);

  for (int i = 0; i < n; ++i) {
    cin >> values[i] >> weights[i];
  }

  // vector<vector<bool>> taken(n + 1, vector<bool>(C + 1, false));
  vvi dp(n + 1, vi(C + 1, 0));

  for (int i = 0; i <= n; ++i) {
    for (int w = 0; w <= C; ++w) {
      if (i == 0 || w == 0) {
        dp[i][w] = 0;
      } else if (w - weights[i - 1] < 0) {
        dp[i][w] = dp[i - 1][w];
      } else {
        // if (dp[i - 1][w - weights[i - 1]] + values[i - 1] > dp[i - 1][w]) {
        //   dp[i][w] = dp[i - 1][w - weights[i - 1]] + values[i - 1];
        //   taken[i][w] = true;
        // } else {
        //   dp[i][w] = dp[i - 1][w];
        // }
        dp[i][w] =
            max(dp[i - 1][w], dp[i - 1][w - weights[i - 1]] + values[i - 1]);
      }
    }
  }
  //
  // int res = dp[n][C];
  // cout << res << "\n";
  vi indices;
  int current_w = C;
  for (int i = n; i > 0; --i) {
    if (dp[i][current_w] != dp[i - 1][current_w]) {
      indices.push_back(i - 1);
      current_w -= weights[i - 1];
    }
  }
  // for (int i = n; i > 0; --i) {
  //   if (taken[i][C]) {
  //     indices.push_back(i - 1);
  //     C -= weights[i - 1];
  //   }
  // }
  //
  cout << indices.size() << "\n";
  for (int i = 0; i < indices.size(); ++i) {
    cout << indices[i] << " \n"[i == indices.size() - 1];
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;

  while (cin >> C >> n) {
    solve();
  }

  return 0;
}
