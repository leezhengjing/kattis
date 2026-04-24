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
const int INT_INF = 1e9;
template <class T> T read() {
  T v;
  std::cin >> v;
  return v;
}

void fast_io() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
}

int target_mask;
int N;
int best_res;
vi node_masks(N + 1);
int dfs(int start_idx, int curr_mask, int curr_count) {
  if (curr_mask == target_mask) {
    best_res = min(best_res, curr_count);
    return 0;
  }
  if (curr_count >= best_res) {
    return INT_INF;
  }

  if (start_idx == N + 1)
    return INT_INF;

  int include_count =
      1 + dfs(start_idx + 1, curr_mask | node_masks[start_idx], curr_count + 1);

  int exclude_count = dfs(start_idx + 1, curr_mask, curr_count);

  return min(include_count, exclude_count);
}

void solve() {
  cin >> N;
  target_mask = (1 << N) - 1;
  node_masks.assign(N + 1, 0);

  for (int i = 1; i <= N; ++i) {
    int d;
    cin >> d;
    int mask = 1 << (i - 1);
    for (int j = 0; j < d; ++j) {
      int val;
      cin >> val;
      val--;
      mask |= (1 << val);
    }
    node_masks[i] = mask;
  }

  // int total_states = (1 << N) - 1;
  // int res = N;
  // for (int mask = 0; mask <= total_states; mask++) {
  //   int count = __builtin_popcount(mask);
  //   int covered = 0;
  //   int mask_copy = mask;
  //   while (mask_copy > 0) {
  //     int lowbit = LSOne(mask_copy);
  //     int idx = __builtin_ctz(mask_copy);
  //     covered |= node_masks[idx + 1];
  //     mask_copy &= (mask_copy - 1);
  //   }
  //
  //   if (covered == target_mask) {
  //     res = min(res, count);
  //   }
  // }
  //
  best_res = N;
  best_res = dfs(1, 0, 0);
  cout << min(best_res, N) << "\n";
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
