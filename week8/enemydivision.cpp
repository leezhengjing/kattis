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
  int n, m;
  cin >> n >> m;

  vvi AL(n + 1);
  vi degree(n + 1, 0);
  for (int i = 0; i < m; ++i) {
    int u, v;
    cin >> u >> v;
    AL[u].push_back(v);
    AL[v].push_back(u);
    degree[u]++;
    degree[v]++;
  }

  int largest_deg = 0;
  for (int i = 1; i <= n; ++i) {
    largest_deg = max(largest_deg, degree[i]);
  }

  if (largest_deg <= 1) {
    cout << "1\n";
    for (int i = 1; i <= n; ++i) {
      cout << i << " \n"[i == n];
    }
    return;
  }

  vi group(n + 1, 0);
  queue<int> q;
  vi in_q(n + 1, 0);

  auto count_enemies = [&](int u) {
    int count = 0;
    for (int v : AL[u]) {
      if (group[u] == group[v])
        count++;
    }
    return count;
  };

  for (int i = 1; i <= n; ++i) {
    if (count_enemies(i) > 1) {
      q.push(i);
      in_q[i] = 1;
    }
  }

  while (!q.empty()) {
    int u = q.front();
    q.pop();
    in_q[u] = 0;

    if (count_enemies(u) > 1) {
      group[u] ^= 1;

      for (int v : AL[u]) {
        if (!in_q[v] && count_enemies(v) > 1) {
          q.push(v);
          in_q[v] = 1;
        }
      }
    }
  }

  cout << 2 << "\n";

  vi grp1, grp2;

  for (int i = 1; i <= n; ++i) {
    if (group[i])
      grp1.push_back(i);
    else
      grp2.push_back(i);
  }

  for (int i = 0; i < grp1.size(); ++i) {
    cout << grp1[i] << " \n"[i == grp1.size() - 1];
  }

  for (int i = 0; i < grp2.size(); ++i) {
    cout << grp2[i] << " \n"[i == grp2.size() - 1];
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
