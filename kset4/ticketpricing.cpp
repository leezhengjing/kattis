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

int N, W;
vector<vii> all_weeks_pairs;
int memo[55][305];

int dfs(int week, int tickets_left) {
  if (week > W)
    return 0;
  if (memo[week][tickets_left] != -1) {
    return memo[week][tickets_left];
  }

  int max_sofar = 0;

  for (const auto &[price, sales] : all_weeks_pairs[week]) {
    int num_sold = min(tickets_left, sales);

    int curr_val = (num_sold * price) + dfs(week + 1, tickets_left - num_sold);

    max_sofar = max(max_sofar, curr_val);
  }

  return memo[week][tickets_left] = max_sofar;
}

void solve() {
  cin >> N >> W;
  memset(memo, -1, sizeof(memo));
  all_weeks_pairs.assign(W + 1, vii());

  for (int i = 0; i <= W; ++i) {
    int K;
    cin >> K;

    vi prices(K);
    vi tickets_sold(K);

    for (int j = 0; j < K; ++j) {
      cin >> prices[j];
    }
    for (int j = 0; j < K; ++j) {
      cin >> tickets_sold[j];
    }

    for (int j = 0; j < K; ++j) {
      all_weeks_pairs[i].push_back({prices[j], tickets_sold[j]});
    }
  }

  int res = -1;
  int best_price = -1;

  for (const auto &[price, tickets_sold] : all_weeks_pairs[0]) {
    int num_sold = min(N, tickets_sold);

    int total = (num_sold * price) + dfs(1, N - num_sold);

    if (total > res) {
      res = total;
      best_price = price;
    } else if (total == res) {
      if (best_price == -1 || price < best_price) {
        best_price = price;
      }
    }
  }
  cout << res << "\n";
  cout << best_price << "\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;

  while (t--) {
    // code here
    solve();
  }

  // reading input
  // read int: int n; cin >> n;
  // read line: string s; getline(cin, s);
  // read list/arr: vi arr(n); for(int i=0; i<n; ++i) cin >> arr[i];
  // eof reading: int n; while(cin >> n) { ... }

  return 0;
}
