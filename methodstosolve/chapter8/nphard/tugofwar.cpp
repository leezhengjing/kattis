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

bitset<45001> dp[51];
void solve() {
  int n;
  cin >> n;

  vi weights(n);
  int total_weight = 0;
  for (int i = 0; i < n; ++i) {
    cin >> weights[i];
    total_weight += weights[i];
  }

  dp[0][0] = 1;

  int people_limit = n / 2;
  for (int w : weights) {
    for (int k = people_limit; k >= 1; --k) {
      dp[k] |= (dp[k - 1] << w);
    }
  }

  int best_w1 = 0;
  int min_diff = total_weight;

  for (int w = 0; w <= total_weight; ++w) {
    if (dp[people_limit][w]) {
      int w2 = total_weight - w;
      if (abs(w - w2) < min_diff) {
        min_diff = abs(w - w2);
        best_w1 = w;
      }
    }
  }

  int team1 = best_w1;
  int team2 = total_weight - best_w1;
  if (team1 > team2)
    swap(team1, team2);

  cout << team1 << " " << team2 << "\n";
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
