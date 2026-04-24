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

void fast_io() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
}

void solve() {
  int n, m, d;
  cin >> n >> m >> d;

  unordered_map<string, int> string_to_id;
  int idx = 0;

  auto get_idx = [&](const string &s) {
    if (!string_to_id.count(s)) {
      string_to_id[s] = ++idx;
    }
    return string_to_id[s];
  };

  vvi AL(n + 1);
  vi in_degree(n + 1, 0);

  unordered_set<string> seen;

  for (int i = 0; i < m; ++i) {
    string a, b;
    cin >> a >> b;

    string edge_hash = a + "-" + b;
    if (!seen.count(edge_hash)) {
      seen.insert(edge_hash);
      int u = get_idx(a);
      int v = get_idx(b);
      AL[u].push_back(v);
      in_degree[v]++;
    }
  }
  queue<int> q;
  for (int i = 1; i <= n; ++i) {
    if (in_degree[i] == 0) {
      q.push(i);
    }
  }

  vi actual_ranking;
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    actual_ranking.push_back(u);
    for (int v : AL[u]) {
      if (--in_degree[v] == 0) {
        q.push(v);
      }
    }
  }

  vi idx_to_rank(n + 1, 0);

  for (int i = 0; i < n; ++i) {
    idx_to_rank[actual_ranking[i]] = i + 1;
  }

  vi typed_mapped;
  for (int i = 0; i < n; ++i) {
    string s;
    cin >> s;
    if (string_to_id.count(s)) {
      int id = string_to_id[s];
      typed_mapped.push_back(idx_to_rank[id]);
    }
  }

  vi tails;
  for (int rank : typed_mapped) {
    auto it = lower_bound(tails.begin(), tails.end(), rank);
    if (it == tails.end()) {
      tails.push_back(rank);
    } else {
      *it = rank;
    }
  }

  cout << 2 * (n - tails.size()) << "\n";
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
