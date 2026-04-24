#include <bits/stdc++.h>
// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/tree_policy.hpp>
using namespace std;
// using namespace __gnu_pbds;

typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<vi> vvi;

#define LSOne(S) ((S) & -(S))
// int two_pow_p1 = LSOne(mask);
// int p1 = __builtin_ctz(two_pow_p1);
#define REP(i, s, t) for (int i = (s); i < (t); ++i)

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
  int n, m;
  cin >> n >> m;

  vector<vii> AL(n + 1, vii());
  vi color(n + 1, -1);
  queue<int> q;
  bool possible = true;

  REP(i, 0, m) {
    int u, v, c;
    cin >> u >> v >> c;
    AL[u].push_back({v, c});
    AL[v].push_back({u, c});

    if (c == 0) {
      if (color[u] == 1 || color[v] == 1)
        possible = false;
      if (color[u] == -1) {
        color[u] = 0;
        q.push(u);
      }
      if (color[v] == -1) {
        color[v] = 0;
        q.push(v);
      };
    } else if (c == 2) {
      if (color[u] == 0 || color[v] == 0)
        possible = false;
      if (color[u] == -1) {
        color[u] = 1;
        q.push(u);
      }
      if (color[v] == -1) {
        color[v] = 1;
        q.push(v);
      }
    }
  }

  if (!possible) {
    cout << "impossible\n";
    return;
  }

  while (!q.empty()) {
    int u = q.front();
    q.pop();

    for (auto &neighbor : AL[u]) {
      int v = neighbor.first;
      int type = neighbor.second;
      int req = (type == 1) ? !color[u] : (type == 2 ? 1 : 0);

      if (color[v] != -1 && color[v] != req) {
        cout << "impossible\n";
        return;
      }
      if (color[v] == -1) {
        color[v] = req;
        q.push(v);
      }
    }
  }

  int res = 0;

  REP(i, 1, n + 1) {
    if (color[i] == 1)
      res++;
  }

  REP(i, 1, n + 1) {
    if (color[i] == -1) {
      int count_zeroes = 0;
      int count_ones = 0;

      color[i] = 0;
      count_zeroes++;
      q.push(i);

      bool possible = true;
      while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (auto &neighbor : AL[u]) {
          int v = neighbor.first;
          int type = neighbor.second;

          int req = (type == 1) ? !color[u] : (type == 2 ? 1 : 0);

          if (color[v] != -1 && color[v] != req) {
            possible = false;
          }

          if (color[v] == -1) {
            color[v] = req;
            if (req == 0)
              count_zeroes++;
            else
              count_ones++;
            q.push(v);
          }
        }
      }
      if (!possible) {
        cout << "impossible\n";
        return;
      }

      res += min(count_zeroes, count_ones);
    }
  }

  cout << res << "\n";
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
