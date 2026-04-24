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

int MAXN = 2e5 + 5;

int dfs(int u, const vvi &AL, const vvi &color_to_stack_idx, const vi &top,
        const vi &bot, vector<bool> &visited_color, vector<bool> &visited_stack,
        vector<bool> &color_in_top) {

  int pair_count = 0;
  for (int stack_idx : color_to_stack_idx[u]) {
    if (visited_stack[stack_idx])
      continue;
    visited_stack[stack_idx] = true;
    if (color_in_top[top[stack_idx]]) {
      pair_count++;
      // cout << top[stack_idx] << " " << u << " ";
      visited_color[bot[stack_idx]] = true;
    }
    // cout << "\n";
    color_in_top[top[stack_idx]] = true;
  }
  for (auto v : AL[u]) {
    if (visited_color[v])
      continue;
    visited_color[v] = true;
    pair_count += dfs(v, AL, color_to_stack_idx, top, bot, visited_color,
                      visited_stack, color_in_top);
  }

  return pair_count;
}

void solve() {
  int n;
  cin >> n;
  vi top(n);
  vi bot(n);

  vvi color_to_stack_idx(n + 1);
  for (int i = 0; i < n; ++i) {
    cin >> top[i];
    color_to_stack_idx[top[i]].push_back(i);
  }
  for (int i = 0; i < n; ++i) {
    cin >> bot[i];
    color_to_stack_idx[bot[i]].push_back(i);
  }

  vvi AL(n + 1, vi());
  for (int i = 0; i < n; ++i) {
    AL[top[i]].push_back(bot[i]);
    AL[bot[i]].push_back(top[i]);
  }

  // for (auto idx_arr : color_to_stack_idx) {
  //   for (auto idx : idx_arr) {
  //     cout << idx << " ";
  //   }
  //   cout << "\n";
  // }
  //

  vector<bool> visited_color(MAXN, false);
  vector<bool> visited_stack(n + 1, false);
  vector<bool> color_in_top(MAXN, false);

  for (int i = 1; i <= n; ++i) {
    visited_color[i] = true;
    int res = dfs(i, AL, color_to_stack_idx, top, bot, visited_color,
                  visited_stack, color_in_top);
    if (res > 1) {
      cout << "NO\n";
      return;
    }
  }
  cout << "YES\n";
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
