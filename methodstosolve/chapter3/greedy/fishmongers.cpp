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
  int n, m;
  cin >> n >> m;

  vll fish(n);

  for (int i = 0; i < n; ++i) {
    cin >> fish[i];
  }

  sort(fish.begin(), fish.end(), greater<ll>());

  vector<pair<ll, ll>> fishmongers(m);
  for (int i = 0; i < m; ++i) {
    ll fish_count, money_per_kg;
    cin >> fish_count >> money_per_kg;
    fishmongers[i] = {money_per_kg, fish_count};
  }

  sort(fishmongers.begin(), fishmongers.end(), greater<pair<ll, ll>>());

  ll res = 0;
  int left = 0;
  for (const auto &[money_per_kg, fish_count] : fishmongers) {
    for (int i = 0; i < fish_count; ++i) {
      if (left >= n)
        break;
      res += fish[left] * money_per_kg;
      left++;
    }
  }

  cout << res << "\n";
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
