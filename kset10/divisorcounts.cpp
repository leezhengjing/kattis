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

const int MAXN = 10000010;
int spf[MAXN]; // Smallest Prime Factor
vector<int> primes;

void sieve() {
  iota(spf, spf + MAXN, 0);
  for (int i = 2; i * i < MAXN; i++) {
    if (spf[i] == i) { // i is prime
      for (int j = i * i; j < MAXN; j += i)
        if (spf[j] == j)
          spf[j] = i;
    }
  }
  for (int i = 2; i < MAXN; i++) {
    if (spf[i] == i)
      primes.push_back(i);
  }
}
ll numDiv(ll n) {
  ll ans = 1;
  // FAST PATH
  if (n < MAXN) {
    while (n != 1) {
      int p = spf[n];
      ll power = 0;
      while (n % p == 0) {
        n /= p;
        power++;
      }
      ans *= (power + 1);
    }
    return ans;
  }
  // SLOW PATH
  for (int p : primes) {
    if (1LL * p * p > n)
      break;
    ll power = 0;
    while (n % p == 0) {
      n /= p;
      power++;
    }
    ans *= (power + 1);
  }
  return (n != 1) ? ans * 2 : ans;
}

void solve() {
  // ll N;
  // cin >> N;
  // for (int i = 1; i <= N; ++i) {
  //   cout << numDiv(i) << "\n";
  // }
  int N;
  cin >> N;

  vector<int> divCount(N + 1, 0);

  for (int i = 1; i <= N; ++i) {
    for (int j = i; j <= N; j += i) {
      divCount[j]++;
    }
  }

  for (int i = 1; i <= N; ++i) {
    cout << divCount[i] << "\n";
  }
}

int main() {
  // sieve();
  fast_io();

  int t = 1;
  // cin >> t;

  while (t--) {
    solve();
  }

  return 0;
}
