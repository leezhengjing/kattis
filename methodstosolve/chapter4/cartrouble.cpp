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

bool reachable[1005];
bool not_trapped[1005];

void solve() {
  int n;
  cin >> n;
  vvi AL(1005);
  vvi reverse_AL(1005);

  vi order(n);

  bool any_trapped = false, any_unreachable = false;
  for (int i = 0; i < n; ++i) {
    int idx, n_streets;
    cin >> idx >> n_streets;
    order[i] = idx;
    for (int j = 0; j < n_streets; ++j) {
      int node;
      cin >> node;
      AL[idx].push_back(node);
      reverse_AL[node].push_back(idx);
    }
  }

  queue<int> q;

  q.push(0);
  reachable[0] = true;

  while (!q.empty()) {
    int curr = q.front();
    q.pop();

    for (auto neighbor : AL[curr]) {
      if (reachable[neighbor])
        continue;
      q.push(neighbor);
      reachable[neighbor] = true;
    }
  }

  q = queue<int>();
  q.push(0);
  not_trapped[0] = true;

  while (!q.empty()) {
    int curr = q.front();
    q.pop();

    for (auto neighbor : reverse_AL[curr]) {
      if (not_trapped[neighbor])
        continue;
      q.push(neighbor);
      not_trapped[neighbor] = true;
    }
  }

  for (auto idx : order) {
    if (!not_trapped[idx]) {
      cout << "TRAPPED " << idx << "\n";
      any_trapped = true;
    }
  }

  for (auto idx : order) {
    if (!reachable[idx]) {
      cout << "UNREACHABLE " << idx << "\n";
      any_unreachable = true;
    }
  }

  if (!any_unreachable && !any_trapped)
    cout << "NO PROBLEMS\n";
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
