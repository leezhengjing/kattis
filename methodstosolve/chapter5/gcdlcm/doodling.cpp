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
  int n, m;
  cin >> n >> m;
  ll H, W, G, K;
  H = n - 1;
  W = m - 1;
  G = gcd(H, W);
  K = 2 * G;

  auto count_X = [&](ll c) -> ll { return H / K + (c <= H % K ? 1 : 0); };
  auto count_Y = [&](ll c) -> ll { return W / K + (c <= W % K ? 1 : 0); };

  ll total_unique = 0;

  total_unique += count_X(0) * count_Y(0);
  total_unique += count_X(G) * count_Y(G);

  if (G > 1) {
    long long term1 = count_X(1) * (count_Y(1) + count_Y(K - 1));
    total_unique += term1 * (G - 1);

    long long term2 = count_X(K - 1) * (count_Y(K - 1) + count_Y(1));
    total_unique += term2 * (G - 1);
  }

  cout << total_unique << "\n";
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;

  while (t--) {
    solve();
  }

  return 0;
}
