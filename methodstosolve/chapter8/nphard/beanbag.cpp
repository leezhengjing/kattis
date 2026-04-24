#include <bits/stdc++.h>
// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/tree_policy.hpp>
using namespace std;
// using namespace __gnu_pbds;

typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
// typedef tuple<int, ll, ll> edge;
typedef tuple<int, ll, ll, ll> edge;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<vi> vvi;

#define LSOne(S) ((S) & -(S))
// int two_pow_p1 = LSOne(mask);
// int p1 = __builtin_ctz(two_pow_p1);
#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define sz(x) (int)(x).size()

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
int B;
vi accepted;

void solve() {
  cin >> B;
  vi arr(B);
  int total = 0;
  for (int i = 0; i < B; ++i) {
    cin >> arr[i];
    total += arr[i];
  }

  int T;
  cin >> T;
  accepted.assign(T, 0);
  for (int i = 0; i < T; ++i) {
    int M;
    cin >> M;
    int mask = 0;
    for (int j = 0; j < M; ++j) {
      int val;
      cin >> val;
      val--;
      mask |= (1 << val);
    }
    accepted[i] = mask;
  }

  int res = total;
  int total_states = (1 << B) - 1;
  for (int state = 0; state <= total_states; state++) {
    int c = state;
    bool is_valid = true;
    for (int j = 0; j < T; ++j) {
      if (!(c & accepted[j])) {
        is_valid = false;
        break;
      }
    }

    if (is_valid) {
      int curr = 0;
      while (c > 0) {
        curr += arr[__builtin_ctz(c)];
        c &= (c - 1);
      }
      res = min(curr, res);
    }
  }

  cout << total - res << "\n";
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
