#include <bits/stdc++.h>

// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/tree_policy.hpp>
using namespace std;
// using namespace __gnu_pbds;

typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef tuple<int, ll, ll> edge;
// typedef tuple<int, ll, ll, ll> edge;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<vi> vvi;

#define LSOne(S) ((S) & -(S))
// int two_pow_p1 = LSOne(mask);
// int p1 = __builtin_ctz(two_pow_p1);
#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define sz(x) (int)(x).size()

const ll INF = 1e18;
const int MOD = 1e9 + 7;

void fast_io() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
}

struct State {
  int r, c, k;
};

void solve() {
  int n;
  cin >> n;

  string s;
  cin >> s;

  string target = "ICPCASIASG";
  int target_len = target.length();

  vii moves = {{1, 2}, {1, -2}, {-1, 2}, {-1, -2},
               {2, 1}, {2, -1}, {-2, 1}, {-2, -1}};

  queue<State> q;
  vector<vector<vector<bool>>> visited(
      n, vector<vector<bool>>(n, vector<bool>(target_len, false)));

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      if (s[i * n + j] == target[0]) {
        q.push({i, j, 0});
        visited[i][j][0] = true;
      }
    }
  }

  while (!q.empty()) {
    State curr = q.front();
    q.pop();

    if (curr.k == target_len - 1) {
      cout << "YES\n";
      return;
    }

    int next_k = curr.k + 1;
    char next_char = target[next_k];

    for (const auto &move : moves) {
      int nr = curr.r + move.first;
      int nc = curr.c + move.second;

      if (nr >= 0 && nr < n && nc >= 0 && nc < n) {
        if (s[nr * n + nc] == next_char && !visited[nr][nc][next_k]) {
          visited[nr][nc][next_k] = true;
          q.push({nr, nc, next_k});
        }
      }
    }
  }

  cout << "NO\n";
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
