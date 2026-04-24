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

int n;
double l, w;

void solve() {
  // cin.ignore(numeric_limits<streamsize>::max(), '\n');

  vector<pair<double, double>> intervals;

  for (int i = 0; i < n; ++i) {
    double x, r;
    cin >> x >> r;

    if (r * 2 <= w)
      continue;

    double width_covered_dist = sqrt(r * r - (w / 2.0) * (w / 2.0));
    double start = x - width_covered_dist, end = x + width_covered_dist;

    intervals.push_back({start, end});
  }

  sort(intervals.begin(), intervals.end());

  int res = 0;
  double current_covered = 0.0;
  int i = 0;
  int sz = intervals.size();

  while (current_covered < l) {
    double max_reach = -1.0;
    bool found_candidate = false;

    while (i < sz && intervals[i].first <= current_covered) {
      max_reach = max(max_reach, intervals[i].second);
      found_candidate = true;
      i++;
    }

    if (!found_candidate || max_reach <= current_covered) {
      cout << "-1\n";
      return;
    }

    res++;
    current_covered = max_reach;
  }

  cout << res << "\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;

  while (cin >> n >> l >> w) {
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
