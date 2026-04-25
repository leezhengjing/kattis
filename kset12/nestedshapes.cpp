#include <bits/stdc++.h>

// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/tree_policy.hpp>
using namespace std;
// using namespace __gnu_pbds;

typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef tuple<int, ll, ll> edge;
// typedef tuple<int, ll, ll, ll> edge;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<vi> vvi;

#define LSOne(S) ((S) & -(S))
// int two_pow_p1 = LSOne(mask);
// int p1 = __builtin_ctz(two_pow_p1);
#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define sz(x) (int)(x).size()

const ll INF = 1e18;
const int MOD = 1e9 + 7;

void fast_io() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
}

void solve() {
  int n;
  string shapes;
  cin >> n >> shapes;
  char inType;
  double inVal;
  cin >> inType >> inVal;

  char outType;
  cin >> outType;

  double r = 0.0;
  char firstShape = shapes[0];

  if (firstShape == 'C') {
    if (inType == 'A')
      r = sqrt(inVal / M_PI);
    else
      r = inVal / (2.0 * M_PI);
  } else if (firstShape == 'S') {
    if (inType == 'A')
      r = sqrt(inVal / 4.0);
    else
      r = inVal / 8.0;
  } else if (firstShape == 'D') {
    if (inType == 'A')
      r = sqrt(inVal / 2.0);
    else
      r = inVal / (4.0 * sqrt(2.0));
  }

  // 2. Apply the continuous scale factors down the chain
  for (int i = 0; i < n - 1; ++i) {
    char from = shapes[i];
    char to = shapes[i + 1];

    if (from == 'C' && to == 'S')
      r *= (1.0 / sqrt(2.0));
    else if (from == 'C' && to == 'D')
      r *= 1.0;
    else if (from == 'S' && to == 'C')
      r *= 1.0;
    else if (from == 'S' && to == 'D')
      r *= 1.0;
    else if (from == 'D' && to == 'C')
      r *= (1.0 / sqrt(2.0));
    else if (from == 'D' && to == 'S')
      r *= 0.5;
  }

  char lastShape = shapes[n - 1];
  double ans = 0.0;

  if (lastShape == 'C') {
    if (outType == 'A')
      ans = M_PI * r * r;
    else
      ans = 2.0 * M_PI * r;
  } else if (lastShape == 'S') {
    if (outType == 'A')
      ans = 4.0 * r * r;
    else
      ans = 8.0 * r;
  } else if (lastShape == 'D') {
    if (outType == 'A')
      ans = 2.0 * r * r;
    else
      ans = 4.0 * sqrt(2.0) * r;
  }

  cout << fixed << setprecision(10) << ans << "\n";
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
