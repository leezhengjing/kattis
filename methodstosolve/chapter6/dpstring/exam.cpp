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
  int n;
  string A, B;
  cin >> n >> A >> B;

  int match_count = 0;
  for (int i = 0; i < A.size(); ++i) {
    if (A[i] == B[i])
      match_count++;
  }

  int res = min(match_count, n) + min(A.length() - n, A.length() - match_count);
  // if (match_count <= n) {
  //   res += match_count;
  //   res += A.length() - n;
  // } else {
  //   res += match_count;
  //   res += A.length() - match_count;
  // }

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
