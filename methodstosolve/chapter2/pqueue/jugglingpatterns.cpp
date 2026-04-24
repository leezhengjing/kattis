#include <bits/stdc++.h>
// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/tree_policy.hpp>
using namespace std;
// using namespace __gnu_pbds;

typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef tuple<int, ll, ll> edge;
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

string s;
void fast_io() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
}

void solve() {
  int n = s.size();
  int sum = 0;
  for (int i = 1; i <= n; ++i) {
    sum += s[i - 1] - '0';
  }
  if (sum % n != 0) {
    cout << s << ": invalid # of balls\n";
    return;
  }
  int l = sum / n;
  vector<bool> arr(n, false);
  bool is_valid = true;
  for (int i = 1; i <= n; ++i) {
    int idx = (s[i - 1] - '0' + i) % n;
    if (arr[idx]) {
      // cerr << "found invalid at index: " << i << "\n";
      is_valid = false;
      break;
    }
    arr[idx] = true;
  }

  if (is_valid) {
    cout << s << ": valid with " << l << " balls\n";
  } else {
    cout << s << ": invalid pattern\n";
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;

  while (cin >> s) {
    solve();
  }

  return 0;
}
