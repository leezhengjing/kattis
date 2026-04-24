#include <bits/stdc++.h>
// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/tree_policy.hpp>
using namespace std;
// using namespace __gnu_pbds;

typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> ii;
typedef tuple<ll, int, int> iii;
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

ll get_dist_sq(ii a, ii b) {
  ll dx = a.first - b.first;
  ll dy = a.second - b.second;
  return dx * dx + dy * dy;
}

void solve() {
  int n, m, p;
  cin >> n >> m >> p;

  vii judges(n);
  vii tars(m);
  vii feathers(p);

  for (int i = 0; i < n; ++i) {
    cin >> judges[i].first >> judges[i].second;
  }

  for (int i = 0; i < m; ++i) {
    cin >> tars[i].first >> tars[i].second;
  }
  for (int i = 0; i < p; ++i) {
    cin >> feathers[i].first >> feathers[i].second;
  }

  double res = 0.0;

  vector<iii> tar_edges;
  tar_edges.reserve(n * m);

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      ll dist_sq = get_dist_sq(tars[j], judges[i]);
      tar_edges.push_back({dist_sq, i, j});
    }
  }

  sort(tar_edges.begin(), tar_edges.end());

  vector<bool> judge_visited(n, false);
  vector<bool> tar_visited(m, false);

  for (const auto &[dist_sq, judge_id, tar_id] : tar_edges) {
    if (!judge_visited[judge_id] && !tar_visited[tar_id]) {
      judge_visited[judge_id] = true;
      tar_visited[tar_id] = true;
      res += sqrt(dist_sq);
    }
  }

  vector<iii> feather_edges;
  feather_edges.reserve(n * p);

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < p; ++j) {
      feather_edges.push_back({get_dist_sq(judges[i], feathers[j]), i, j});
    }
  }
  sort(feather_edges.begin(), feather_edges.end());

  vector<bool> feather_visited(p, false);
  judge_visited = vector<bool>(n, false);
  for (const auto &[dist_sq, judge_id, feather_id] : feather_edges) {
    if (!judge_visited[judge_id] && !feather_visited[feather_id]) {
      judge_visited[judge_id] = true;
      feather_visited[feather_id] = true;
      res += sqrt(dist_sq);
    }
  }

  cout << fixed << setprecision(6) << res << " \n";
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
