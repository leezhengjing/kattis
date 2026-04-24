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
  // cin.ignore(numeric_limits<streamsize>::max(), '\n');
  int N, K;
  cin >> N >> K;

  vi prices(N);

  for (int i = 0; i < N; ++i) {
    cin >> prices[i];
  }

  int max_profit = 0;

  int max_sell_val = -1e9;

  for (int i = 0; i < N; ++i) {
    int curr_sell_val = prices[i] * 100 + K * i;

    if (curr_sell_val > max_sell_val) {
      max_sell_val = curr_sell_val;
    }

    int curr_buy_val = prices[i] * 100 + K * i;

    int profit = max_sell_val - curr_buy_val - K;

    if (profit > max_profit)
      max_profit = profit;
  }

  cout << max_profit << "\n";
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
