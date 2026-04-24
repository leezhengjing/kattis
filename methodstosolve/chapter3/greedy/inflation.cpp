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
  int n;
  cin >> n;
  vi canisters(n);

  bool zero_found = false;
  for (int i = 0; i < n; ++i) {
    int val;
    cin >> val;

    canisters[i] = val;
  }

  sort(canisters.begin(), canisters.end());

  double res = 1.0;

  for (int i = 0; i < n; ++i) {
    if (i + 1 < canisters[i]) {
      cout << "impossible\n";
      return;
    }

    res = min(res, (double)canisters[i] / (i + 1));
  }

  if (zero_found) {
    cout << 0 << "\n";
    return;
  }

  cout << fixed << setprecision(6);
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
