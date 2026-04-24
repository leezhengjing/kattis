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

int M;
int total_masks;

// bool dfs(int curr_mask) {
//   if (curr_mask == total_masks - 1)
//     return true;
//
//   for (auto sub : valid) {
//     if ((curr_mask & sub) == 0) {
//       int next_mask = curr_mask | sub;
//
//       if (dfs(next_mask))
//         return true;
//     }
//   }
//
//   return false;
// }

void solve() {
  set<string> students;
  // need to get like a workwell[name1][name2], vector<string><string> ?
  // better if can map name to int
  //
  vector<pair<string, string>> matchings;
  map<string, int> name_to_idx;
  for (int i = 0; i < M; ++i) {
    string u, v;
    cin >> u >> v;
    students.insert(u);
    students.insert(v);
    matchings.push_back({u, v});
  }

  int N = students.size();
  vector<vector<bool>> AM(N, vector<bool>(N, false));
  for (auto &[u, v] : matchings) {
    // ok TIL 0 indexed for first item in set with distance
    auto it1 = students.find(u);
    auto dist1 = distance(students.begin(), it1);
    auto it2 = students.find(v);
    auto dist2 = distance(students.begin(), it2);
    AM[dist1][dist2] = true;
    AM[dist2][dist1] = true;
    // cout << dist1 << " " << dist2 << "\n";
  }

  // ok we got the min clique edges now in AM, now we need to find all valid
  // cliques, 2 ^ 15 = 32768?
  //
  total_masks = 1 << N;
  // this was 6 for tc 1
  // 1 << 6 =  1 0 0 0 0 0 0
  //  -1 =  111111;
  //  1 2 4 8 9 16 32 34
  //  wait ofc it will be possible, ive enabled single digit ?? LOL
  //  only valid ones are now 3 bits set masks, but now i print out nothing?
  //  1 - 10 - 100 - 1000 - 100
  //
  //   4 3
  //   4 0
  //   0 3
  //   3 1
  //   5 0
  //   2 1
  //   1 5
  //   5 2
  // shouldnt i minimally alr get one 3 bit bitmask from 4 3 0 alr?
  // fuck never set both uv and vu to true;
  // 2^4 = 16 + 2^3 = 8 + 2^0 = 1 = 25
  // why 25 returns false?
  vector<bool> valid(total_masks, false);

  for (int mask = 1; mask < total_masks; ++mask) {
    if (__builtin_popcount(mask) != 3) {
      continue;
    }
    bool is_valid = true;
    for (int i = 0; i < N && is_valid; ++i) {
      if (!(mask & (1 << i)))
        continue;
      for (int j = i + 1; j < N && is_valid; ++j) {
        if (!(mask & (1 << j)))
          continue;

        if (!(AM[i][j])) {
          is_valid = false;
        }
      }
    }
    valid[mask] = is_valid;
    // if (is_valid) {
    //   valid.push_back(mask);
    // }
  }

  // now we got all the valid masks (cliques)m we need find possible to no
  // to group all students (total mask)

  vector<bool> dp(total_masks, false);
  dp[0] = true;
  // 0 cliques required togroup 0 students, ie. is possible to grp 0 students
  // (trivially)
  for (int mask = 1; mask < total_masks; ++mask) {
    // ??? what am i doign here... this is too much i think dont bottom up
    for (int ss = mask; ss > 0; ss = (ss - 1) & mask) {
      if (valid[ss]) {
        int remaining = mask ^ ss;

        if (dp[remaining])
          dp[mask] = true;
      }
    }
  }

  if (dp[total_masks - 1])
    cout << "possible\n";
  else
    cout << "impossible\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;

  while (cin >> M && M != 0) {
    solve();
  }

  return 0;
}
