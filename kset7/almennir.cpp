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

bool is_valid(ll m, ll time, vll const &grill_times) {
  ll burgers = 0;
  for (auto grill_time : grill_times) {
    burgers += time / grill_time;
  }
  return burgers > m;
}

void solve() {
  ll n, m;
  cin >> n >> m;
  ll min_time = INF;
  ll max_time = 0;
  vll grill_times(n);
  for (int i = 0; i < n; ++i) {
    cin >> grill_times[i];
    min_time = min(min_time, grill_times[i]);
    max_time = max(max_time, grill_times[i]);
  }

  ll left = 0, right = (m + 1 + n - 1) / n * max_time;

  ll ans = 0;
  while (left <= right) {
    ll mid = left + (right - left) / 2;

    if (is_valid(m, mid, grill_times)) {
      right = mid - 1;
      ans = mid;
    } else {
      left = mid + 1;
    }
  }

  cout << ans << "\n";
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
