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

namespace CPMath {

// ==========================================
// 3. BASE CONVERSIONS (Up to Base 36)
// ==========================================

// Converts a string in a given base to a base-10 integer
ll toBase10(string s, int base) {
  ll val = 0;
  for (char c : s) {
    int digit = isdigit(c) ? c - '0' : c - 'A' + 10;
    val = val * base + digit;
  }
  return val;
}

// Converts a base-10 integer to a string in a given base
string fromBase10(ll n, int base) {
  if (n == 0)
    return "0";
  string res = "";
  while (n > 0) {
    int digit = n % base;
    res += (digit < 10 ? (char)(digit + '0') : (char)(digit - 10 + 'A'));
    n /= base;
  }
  reverse(res.begin(), res.end());
  return res;
}

// ==========================================
// 1. SIEVE & FAST FACTORIZATION (for N <= 10^7)
// ==========================================
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

// Returns prime factors of N in O(log N) time
// Precondition: N <= MAXN and sieve() has been called
vll primeFactorsFast(ll n) {
  vll factors;
  while (n != 1) {
    factors.push_back(spf[n]);
    n /= spf[n];
  }
  return factors;
}

vll primeFactors(ll N) { // pre-condition, N >= 1
  vll factors;
  for (int i = 0; (i < (int)primes.size()) && (primes[i] * primes[i] <= N); ++i)
    while (N % primes[i] == 0) { // found a prime for N
      N /= primes[i];            // remove it from N
      factors.push_back(primes[i]);
    }
  if (N != 1)
    factors.push_back(N);
  return factors;
}
// remaining N is a prime
// ==========================================
// 2. MODULAR MATH & 64-BIT PRIMALITY
// ==========================================

// Fast modular exponentiation (a^b % m)
ll modpow(ll a, ll b, ll m) {
  ll res = 1;
  a %= m;
  while (b > 0) {
    if (b & 1)
      res = (__int128)res * a % m; // __int128 prevents overflow
    a = (__int128)a * a % m;
    b >>= 1;
  }
  return res;
}

bool isPrimeBasic(ll n) {
  // 1. Handle base cases
  if (n < 2)
    return false;
  if (n == 2 || n == 3)
    return true;
  if (n % 2 == 0 || n % 3 == 0)
    return false;

  // 2. All primes > 3 are of the form 6k ± 1.
  // We only check up to sqrt(n)
  for (ll i = 5; i * i <= n; i += 6) {
    if (n % i == 0 || n % (i + 2) == 0) {
      return false;
    }
  }
  return true;
}

// Deterministic Miller-Rabin for 64-bit integers
// Works for N up to 2^64 - 1
bool isPrime(ll n) {
  if (n < 2)
    return false;
  if (n == 2 || n == 3)
    return true;
  if (n % 2 == 0)
    return false;

  ll d = n - 1;
  int s = 0;
  while (d % 2 == 0) {
    d /= 2;
    s++;
  }

  // These bases guarantee deterministic results for N < 2^64
  static const ll bases[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};

  for (ll a : bases) {
    if (n <= a)
      break;
    ll x = modpow(a, d, n);
    if (x == 1 || x == n - 1)
      continue;

    bool composite = true;
    for (int r = 1; r < s; r++) {
      x = (__int128)x * x % n;
      if (x == n - 1) {
        composite = false;
        break;
      }
    }
    if (composite)
      return false;
  }
  return true;
}

ll numPF(ll n) {
  ll ans = 0;
  // FAST PATH: O(log N) if n is within our sieve limit
  if (n < MAXN) {
    while (n != 1) {
      n /= spf[n];
      ans++;
    }
    return ans;
  }
  // SLOW PATH: O(sqrt N) fallback for large n
  for (int p : primes) {
    if (1LL * p * p > n)
      break;
    while (n % p == 0) {
      n /= p;
      ans++;
    }
  }
  return ans + (n != 1);
}

ll numDiffPF(ll n) {
  ll ans = 0;
  // FAST PATH
  if (n < MAXN) {
    while (n != 1) {
      int p = spf[n];
      ans++;
      while (n % p == 0)
        n /= p;
    }
    return ans;
  }
  // SLOW PATH
  for (int p : primes) {
    if (1LL * p * p > n)
      break;
    if (n % p == 0) {
      ans++;
      while (n % p == 0)
        n /= p;
    }
  }
  return ans + (n != 1);
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

ll EulerPhi(ll n) {
  ll ans = n;
  // FAST PATH
  if (n < MAXN) {
    while (n != 1) {
      int p = spf[n];
      ans -= ans / p;
      while (n % p == 0)
        n /= p;
    }
    return ans;
  }
  // SLOW PATH
  for (int p : primes) {
    if (1LL * p * p > n)
      break;
    if (n % p == 0)
      ans -= ans / p;
    while (n % p == 0)
      n /= p;
  }
  if (n != 1)
    ans -= ans / n;
  return ans;
}

// 5.3.8 Legendre's Formula: highest power of p that divides n!
ll vpFactorial(ll n, ll p) {
  ll res = 0;
  while (n > 0) {
    res += n / p;
    n /= p;
  }
  return res;
}

int gcd(int a, int b) { return b == 0 ? a : gcd(b, a % b); }
int lcm(int a, int b) { return a / gcd(a, b) * b; }

// 5.3.9 & 5.3.10 Modular Arithmetic & Extended Euclid
ll mod(ll a, ll m) { return ((a % m) + m) % m; }

ll extEuclid(ll a, ll b, ll &x, ll &y) {
  if (b == 0) {
    x = 1;
    y = 0;
    return a;
  }
  ll x1, y1;
  ll d = extEuclid(b, a % b, x1, y1);
  x = y1;
  y = x1 - y1 * (a / b);
  return d;
}

ll modInverse(ll a, ll m) {
  ll x, y;
  ll g = extEuclid(a, m, x, y);
  if (g != 1)
    return -1; // Inverse doesn't exist
  return mod(x, m);
}

// Linear Diophantine: Find one solution to ax + by = c
bool find_any_solution(ll a, ll b, ll c, ll &x0, ll &y0, ll &g) {
  g = extEuclid(abs(a), abs(b), x0, y0);
  if (c % g)
    return false;
  x0 *= c / g;
  y0 *= c / g;
  if (a < 0)
    x0 = -x0;
  if (b < 0)
    y0 = -y0;
  return true;
}
} // namespace CPMath

void fast_io() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
}

void solve() {
  string s;
  cin >> s;

  string bin = "";
  string oct2bin[8] = {"000", "001", "010", "011", "100", "101", "110", "111"};

  for (char c : s) {
    bin += oct2bin[c - '0'];
  }
  while (bin.length() % 4 != 0) {
    bin = "0" + bin;
  }

  string hex_out = "";
  for (int i = 0; i < (int)bin.length(); i += 4) {
    int val = 0;
    for (int j = 0; j < 4; j++) {
      val = val * 2 + (bin[i + j] - '0');
    }
    if (val < 10)
      hex_out += (char)(val + '0');
    else
      hex_out += (char)(val - 10 + 'A');
  }

  int start = 0;
  while (start < (int)hex_out.length() - 1 && hex_out[start] == '0') {
    start++;
  }

  cout << hex_out.substr(start) << "\n";
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
