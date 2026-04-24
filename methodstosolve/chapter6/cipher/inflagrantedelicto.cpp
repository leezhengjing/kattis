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

void fast_io() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
}

void solve() {
  int N;
  cin >> N;

  vi P(N), D(N);
  vi p_order(N + 1);
  for (int i = 0; i < N; ++i) {
    cin >> P[i];
    p_order[P[i]] = i;
  }
  for (int i = 0; i < N; ++i) {
    cin >> D[i];
    D[i] = p_order[D[i]];
  }

  vi tails;

  for (int i = 0; i < N; ++i) {
    int val = D[i];
    auto it = lower_bound(tails.begin(), tails.end(), val);
    if (it == tails.end()) {
      tails.push_back(val);
    } else {
      *it = val;
    }
  }
  cout << "2 " << tails.size() + 1 << "\n";
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
