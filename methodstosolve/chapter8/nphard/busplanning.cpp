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

vi color;

void solve() {
  int n, k, c;
  cin >> n >> k >> c;
  color.assign(n, -1);
  vector<string> names(n);
  map<string, int> name_to_idx;
  for (int i = 0; i < n; ++i) {
    cin >> names[i];
    name_to_idx[names[i]] = i;
  }

  vector<vector<bool>> AM(n, vector<bool>(n, false));
  for (int i = 0; i < k; ++i) {
    string u_string, v_string;
    cin >> u_string >> v_string;
    int u = name_to_idx[u_string], v = name_to_idx[v_string];
    AM[u][v] = true;
    AM[v][u] = true;
  }

  int max_mask = 1 << n;
  vector<bool> valid_bus(max_mask, false);
  for (int mask = 1; mask < max_mask; ++mask) {
    if (__builtin_popcount(mask) > c)
      continue;

    bool is_valid = true;
    for (int i = 0; i < n && is_valid; ++i) {
      if ((mask & (1 << i)) == 0)
        continue;

      for (int j = i + 1; j < n && is_valid; ++j) {
        if ((mask & (1 << j)) == 0)
          continue;

        if (AM[i][j])
          is_valid = false;
      }
    }
    valid_bus[mask] = is_valid;
  }

  vi dp(max_mask, INF);
  vi parent(max_mask, 0);

  dp[0] = 0;
  for (int mask = 1; mask < max_mask; ++mask) {
    for (int ss = mask; ss > 0; ss = (ss - 1) & mask) {
      if (valid_bus[ss]) {
        int remaining_kids = mask ^ ss;

        if (dp[remaining_kids] + 1 < dp[mask]) {
          dp[mask] = dp[remaining_kids] + 1;
          parent[mask] = ss;
        }
      }
    }
  }
  int curr_mask = max_mask - 1;

  cout << dp[curr_mask] << "\n";

  while (curr_mask > 0) {
    int bus_mask = parent[curr_mask];

    bool first = true;
    for (int i = 0; i < n; ++i) {
      if (bus_mask & (1 << i)) {
        if (!first)
          cout << " ";
        cout << names[i];
        first = false;
      }
    }
    cout << "\n";

    curr_mask ^= bus_mask;
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
