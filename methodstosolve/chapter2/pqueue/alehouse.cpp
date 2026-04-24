#include <bits/stdc++.h>
// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/tree_policy.hpp>
using namespace std;
// using namespace __gnu_pbds;

typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef tuple<int, ll, ll> edge; // For MaxFlow
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<vi> vvi;

#define LSOne(S) ((S) & -(S))
// int two_pow_p1 = LSOne(mask);
// int p1 = __builtin_ctz(two_pow_p1);
#define REP(i, s, t) for (int i = (s); i < (t); ++i)

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

void solve() {
  ll n, k;
  cin >> n >> k;
  vector<pair<ll, ll>> intervals;
  for (int i = 0; i < n; ++i) {
    ll a, b;
    cin >> a >> b;
    intervals.push_back({a - k, b});
  }
  sort(intervals.begin(), intervals.end());

  priority_queue<ll, vll, greater<ll>> pq;

  int res = 0;
  for (const auto &[start, end] : intervals) {
    while (!pq.empty() && pq.top() < start) {
      pq.pop();
    }
    pq.push(end);
    res = max(res, (int)pq.size());
  }
  cout << res << "\n";
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
