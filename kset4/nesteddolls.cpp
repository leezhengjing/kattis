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

bool compareDolls(const ii &a, const ii &b) {
  if (a.first != b.first) {
    return a.first < b.first;
  }
  return a.second > b.second;
}

void solve() {
  int m;
  cin >> m;

  vii dolls(m);
  for (int i = 0; i < m; ++i) {
    int w, h;
    cin >> w >> h;

    dolls[i] = {w, h};
  }

  sort(dolls.begin(), dolls.end(), compareDolls);

  // vi dp(m, 1);
  //
  // int res = 1;
  // for (int i = 0; i < m; ++i) {
  //   for (int j = 0; j < i; ++j) {
  //     if (dolls[j].second >= dolls[i].second) {
  //       dp[i] = max(dp[i], dp[j] + 1);
  //       res = max(dp[i], res);
  //     }
  //   }
  // }
  vi tails;

  for (const auto &doll : dolls) {
    int h = doll.second;

    if (tails.empty() || h <= tails.back()) {
      tails.push_back(h);
    } else {
      auto it = upper_bound(tails.begin(), tails.end(), h, greater<int>());

      if (it != tails.end())
        *it = h;
    }
  }

  cout << tails.size() << "\n";
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;

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
