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

struct Drink {
  string name;
  int id;
  int cost_scaled;
  int units_scaled; // strength * size_str * 60;
};

int dp[1005][1205];

void solve() {
  double m, u;
  int d;

  cin >> m >> u >> d;

  int M, U;

  M = round(m * 100);
  U = round(u * 60);

  vector<Drink> drinks(d);

  for (int i = 0; i < d; ++i) {
    string drink_name, size_str;
    int strength;
    double cost;
    cin >> drink_name >> strength >> size_str >> cost;

    int cost_scaled = round(cost * 100);
    int units_scaled = 0;

    if (size_str == "1/1")
      units_scaled = strength * 60;
    else if (size_str == "1/2")
      units_scaled = strength * 30;
    else if (size_str == "1/3")
      units_scaled = strength * 20;

    drinks[i] = {drink_name, i, cost_scaled, units_scaled};
  }

  for (int i = 0; i <= M; ++i) {
    for (int j = 0; j <= U; ++j) {
      dp[i][j] = -1;
    }
  }

  dp[0][0] = -2;

  for (int k = 0; k < d; ++k) {
    int cost = drinks[k].cost_scaled;
    int units = drinks[k].units_scaled;

    for (int i = cost; i <= M; ++i) {
      for (int j = units; j <= U; ++j) {
        if (dp[i - cost][j - units] != -1) {
          dp[i][j] = k;
        }
      }
    }
  }

  if (dp[M][U] == -1) {
    cout << "IMPOSSIBLE" << "\n";
    return;
  }

  vi counts(d, 0);
  int curr_m = M;
  int curr_u = U;

  while (curr_m > 0 || curr_u > 0) {
    int drink_idx = dp[curr_m][curr_u];

    if (drink_idx == -2)
      break;

    counts[drink_idx]++;
    curr_m -= drinks[drink_idx].cost_scaled;
    curr_u -= drinks[drink_idx].units_scaled;
  }

  for (int i = 0; i < d; ++i) {
    if (counts[i] > 0) {
      cout << drinks[i].name << " " << counts[i] << "\n";
    }
  }
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
