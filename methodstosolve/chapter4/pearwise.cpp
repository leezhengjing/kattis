#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<vi> vvi;

#define LSOne(S) ((S) & -(S))
#define REP(i, s, t) for (int i = (s); i < (t); ++i)

void fast_io() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
}

int n, m;
// model the graph AM[u][v] = number of u > v ? then when we finish a 1v1, we
// dont need  to delete anything, we do dfs and try and for ma path that makes a
// cc of n components?
//
int AM[30][30];
int reach[30][30];
// bool visited[30];
//
// int dfs(int u) {
//
//   int count = 1;
//   visited[u] = true;
//   for (int v = 0; v < n; ++v) {
//     if (visited[v] || u == v)
//       continue;
//     if (AM[u][v] > AM[v][u]) {
//       visited[v] = true;
//       count = max(count, 1 + dfs(v));
//       if (count == n)
//         return count;
//       visited[v] = false;
//     }
//   }
//   return count;
// }
//
void solve() {
  cin >> n >> m;

  memset(AM, 0, sizeof(AM));

  for (int i = 0; i < m; ++i) {
    int p;
    string s;
    cin >> p >> s;
    for (int j = 0; j < n; ++j) {
      int curr = s[j] - 'A';
      for (int k = 0; k < j; ++k) {
        int prev = s[k] - 'A';
        AM[prev][curr] += p;
      }
    }
  }
  for (int i = 0; i < n; ++i) {
    reach[i][i] = true;
    for (int j = 0; j < n; ++j) {
      if (i != j && AM[i][j] > AM[j][i]) {
        reach[i][j] = true;
      }
    }
  }

  for (int k = 0; k < n; ++k) {
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        reach[i][j] |= reach[i][k] && reach[k][j];
      }
    }
  }

  for (int i = 0; i < n; ++i) {
    bool can_win = true;
    for (int j = 0; j < n; ++j) {
      if (!reach[i][j]) {
        can_win = false;
        break;
      }
    }
    char letter = (char)(i + 'A');
    if (can_win) {
      cout << letter << ": can win\n";
    } else {
      cout << letter << ": can't win\n";
    }
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
