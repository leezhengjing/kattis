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

bool isPrimeBasic(ll n) {
  if (n < 2)
    return false;
  if (n == 2 || n == 3)
    return true;
  if (n % 2 == 0 || n % 3 == 0)
    return false;

  for (ll i = 5; i * i <= n; i += 6) {
    if (n % i == 0 || n % (i + 2) == 0) {
      return false;
    }
  }
  return true;
}

template <typename T, typename F> pair<int, int> floydCycleFinding(T x0, F f) {
  // Part 1: Find a multiple of lambda (k * lambda)
  // Hare moves 2x as fast as the tortoise
  T tortoise = f(x0);
  T hare = f(f(x0));
  while (tortoise != hare) {
    tortoise = f(tortoise);
    hare = f(f(hare));
  }

  // Part 2: Find mu (start of the cycle)
  // Move hare back to start, both move at 1x speed
  int mu = 0;
  hare = x0;
  while (tortoise != hare) {
    tortoise = f(tortoise);
    hare = f(hare);
    mu++;
  }

  // Part 3: Find lambda (length of cycle)
  // Tortoise stays still, hare moves at 1x speed until they meet again
  int lambda = 1;
  hare = f(tortoise);
  while (tortoise != hare) {
    hare = f(hare);
    lambda++;
  }

  return {mu, lambda};
}

void solve() {
  int K, m;
  cin >> K >> m;

  if (!isPrimeBasic(m)) {
    cout << K << " " << m << " NO\n";
    return;
  }

  auto transition = [](int x) {
    int res = 0;
    while (x > 0) {
      int val = x % 10;
      res += val * val;
      x /= 10;
    }
    return res;
  };

  ii cycle = floydCycleFinding(m, transition);
  int cycle_val = m;
  for (int i = 0; i < cycle.first; ++i) {
    cycle_val = transition(cycle_val);
  }
  if (cycle_val == 1) {
    cout << K << " " << m << " YES\n";
  } else {
    cout << K << " " << m << " NO\n";
  }
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
