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

const int INF = 1e9;

void fast_io() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
}

int N;
void solve() {
  cin >> N;
  vector<vector<bool>> AM(N, vector<bool>(N));
  string line;
  getline(cin, line);
  for (int i = 0; i < N; ++i) {
    getline(cin, line);
    stringstream ss(line);

    int val;
    while (ss >> val) {
      AM[i][val] = true;
      AM[val][i] = true;
    }
  }

  int total_masks = 1 << N;
  vector<bool> valid_clique(total_masks);

  for (int mask = 1; mask < total_masks; ++mask) {
    bool is_valid = true;
    for (int i = 0; i < N && is_valid; ++i) {
      if (!(mask & (1 << i)))
        continue;
      for (int j = i + 1; j < N; ++j) {
        if (!(mask & (1 << j)))
          continue;

        if (AM[i][j]) {
          is_valid = false;
        }
      }
    }
    valid_clique[mask] = is_valid;
  }

  vi dp(total_masks, INF);
  dp[0] = 0; // 0 colors required for 0 vertices

  for (int mask = 1; mask < total_masks; ++mask) {
    for (int ss = mask; ss; ss = (ss - 1) & mask) {
      if (valid_clique[ss]) {
        dp[mask] = min(dp[mask], 1 + dp[mask ^ ss]);
      }
    }
  }

  cout << dp[total_masks - 1] << "\n";

  // for (auto AL : AM) {
  //   for (auto val : AL) {
  //     cout << val << " ";
  //   }
  //   cout << "\n";
  // }
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
