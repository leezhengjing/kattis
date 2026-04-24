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

void solve() {
  int N, S;
  cin >> N >> S;

  vll blocks(N);
  vll skyline(S);
  for (int i = 0; i < N; ++i) {
    cin >> blocks[i];
  }
  for (int i = 0; i < S; ++i) {
    cin >> skyline[i];
  }
  int max_mask = 1 << N;
  vll sum(max_mask, 0);

  for (int mask = 1; mask < max_mask; ++mask) {
    int low_bit = LSOne(mask);
    int idx = __builtin_ctz(low_bit);
    sum[mask] = sum[mask ^ low_bit] + blocks[idx];
  }

  vvi valid(S);
  for (int mask = 1; mask < max_mask; ++mask) {
    for (int k = 0; k < S; ++k) {
      if (sum[mask] == skyline[k]) {
        valid[k].push_back(mask);
      }
    }
  }

  vi dp(max_mask, -1);
  vi parent(max_mask, -1);
  dp[0] = 0;
  for (int k = 0; k < S; ++k) {
    vi curr_layer;
    for (int mask = 0; mask < max_mask; ++mask) {
      if (dp[mask] == k) {
        curr_layer.push_back(mask);
      }
    }

    for (int mask : curr_layer) {
      for (int sub : valid[k]) {
        if ((mask & sub) == 0) {
          int next_mask = mask | sub;

          if (dp[next_mask] < k + 1) {
            dp[next_mask] = k + 1;
            parent[next_mask] = sub;
          }
        }
      }
    }
  }

  int final_mask = -1;
  for (int mask = 0; mask < max_mask; ++mask) {
    if (dp[mask] == S) {
      final_mask = mask;
      break;
    }
  }

  if (final_mask == -1) {
    cout << "-1\n";
    return;
  }

  vvi ans(S);
  int curr = final_mask;
  for (int k = S - 1; k >= 0; --k) {
    int sub = parent[curr];
    for (int i = 0; i < N; ++i) {
      if (sub & (1 << i)) {
        ans[k].push_back(i + 1);
      }
    }
    curr ^= sub;
  }

  for (int k = 0; k < S; ++k) {
    cout << ans[k].size();
    for (int x : ans[k]) {
      cout << " " << x;
    }
    cout << "\n";
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
