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

const int MAXN = 1e6 + 5;
ll fact[MAXN];
ll res_sum[MAXN];

void precompute(ll M) {
  memset(fact, 0, sizeof(fact));
  memset(res_sum, 0, sizeof(res_sum));
  fact[0] = 1;
  res_sum[0] = 1;
  res_sum[1] = 1;
  res_sum[2] = 2;
  for (ll i = 1; i < MAXN; ++i) {
    fact[i] = (fact[i - 1] * i) % M;
    if (i >= 3) {
      res_sum[i] = (res_sum[i - 1] % M + ((i - 1) * res_sum[i - 2]) % M) % M;
    }
  }
}

void fast_io() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
}

void solve(ll M) {
  int N;
  cin >> N;

  cout << (fact[N] - res_sum[N] + M) % M << "\n";
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  ll M;
  cin >> M;
  precompute(M);
  while (t--) {
    solve(M);
  }

  return 0;
}
