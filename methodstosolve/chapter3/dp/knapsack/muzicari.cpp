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
  int T, N;
  cin >> T >> N;

  vi arr(N);
  for (int i = 0; i < N; ++i) {
    cin >> arr[i];
  }

  vector<vector<bool>> dp(N + 1, vector<bool>(T + 1, false));

  int highest_sofar = 0;
  dp[0][0] = 1;
  for (int i = 1; i <= N; ++i) {
    for (int w = 0; w <= T; ++w) {
      if (w - arr[i - 1] < 0) {
        dp[i][w] = dp[i - 1][w];
      } else {
        dp[i][w] = dp[i - 1][w] || dp[i - 1][w - arr[i - 1]];
        highest_sofar = max(highest_sofar, w);
      }
    }
  }

  // for (auto row : dp) {
  //   for (int i = 0; i < row.size(); ++i) {
  //     cout << row[i] << " \n"[i == row.size() - 1];
  //   }
  // }

  int curr_T = highest_sofar;
  int track2 = highest_sofar;

  vi res(N, -1);
  for (int i = N; i > 0; --i) {
    if (dp[i][curr_T] != dp[i - 1][curr_T]) {
      res[i - 1] = curr_T - arr[i - 1];
      curr_T -= arr[i - 1];
    } else {
      res[i - 1] = track2 - arr[i - 1];
      track2 -= arr[i - 1];
    }
  }

  for (int i = 0; i < N; ++i) {
    cout << res[i] << " \n"[i == N - 1];
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
