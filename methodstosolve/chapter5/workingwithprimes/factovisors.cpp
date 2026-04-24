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

// Eulerphi: number of positive integers < n relatively prime to n
// reduces to Fermat if n is prime i.e. phi(n) = n - 1;
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

// returns a^(-1) (mod m) only if a and m are relatively prime i.e. gcd(a, m) ==
// 1
//
// now we can compute ( a / b ) % m = (a * b^(-1)) % m = ((a % m) x
// (modInverse(b, m)) % m);
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

// ==========================================
// 4. COMBINATORICS (Modulo Arithmetic)
// ==========================================
const int MAX_COMB =
    2000010;            // Adjust based on problem (up to 2*10^6 is common)
const ll MOD = 1e9 + 7; // Standard CP modulo

ll fact[MAX_COMB];
ll invFact[MAX_COMB];
ll fib[MAX_COMB];
ll cat[MAX_COMB];

// Precomputes factorials, inverse factorials, Fibonacci, and Catalan numbers in
// O(N)
void initCombinatorics() {
  // 1. Base Cases
  fact[0] = 1;
  invFact[0] = 1;
  fib[0] = 0;
  if (MAX_COMB > 1)
    fib[1] = 1;

  // 2. Compute all factorials: n! % MOD
  for (int i = 1; i < MAX_COMB; ++i) {
    fact[i] = (fact[i - 1] * i) % MOD;
    if (i > 1)
      fib[i] = (fib[i - 1] + fib[i - 2]) % MOD;
  }

  // 3. Compute the inverse of the largest factorial using Fermat's Little
  // Theorem modpow(a, b, m) is already in your template!
  invFact[MAX_COMB - 1] = modpow(fact[MAX_COMB - 1], MOD - 2, MOD);

  // 4. Compute all other inverse factorials backwards in O(1) each
  // Because: 1/(n-1)! = (1/n!) * n
  for (int i = MAX_COMB - 2; i >= 1; --i) {
    invFact[i] = (invFact[i + 1] * (i + 1)) % MOD;
  }
}

// O(1) Binomial Coefficient (n Choose k)
ll nCk(int n, int k) {
  if (k < 0 || k > n)
    return 0;
  // Formula: n! * (k!)^-1 * ((n-k)!)^-1 % MOD
  ll ans = fact[n] * invFact[k] % MOD;
  ans = ans * invFact[n - k] % MOD;
  return ans;
}

// O(1) Catalan Number
// Formula: C(2n, n) / (n + 1)
ll catalan(int n) {
  // To divide by (n+1) modulo MOD, we multiply by its modular inverse
  ll inv_n_plus_1 = modpow(n + 1, MOD - 2, MOD);
  return nCk(2 * n, n) * inv_n_plus_1 % MOD;
}

// ==========================================
// 5. CYCLE FINDING (Floyd's Tortoise and Hare)
// ==========================================

// Returns {mu, lambda} where:
// mu = 0-indexed start of the cycle
// lambda = length of the cycle
// T is the data type (int, ll), F is a lambda function for transitions
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

// ==========================================
// 6. PROBABILITY & GAME THEORY (Cheat Sheet)
// ==========================================
/*
 * ------------------------------------------
 * PROBABILITY & EXPECTED VALUE (EV)
 * ------------------------------------------
 * 1. Linearity of Expectation: E[A + B] = E[A] + E[B]
 * -> The expected value of a sum is the sum of expected values.
 * -> THIS WORKS EVEN IF A AND B ARE DEPENDENT! (Massive CP trick)
 * * 2. Waiting Time (Geometric Distribution):
 * -> If the probability of an event happening is P...
 * -> The expected number of trials to get 1 success is 1 / P.
 * -> (e.g., rolling a specific number on a 6-sided die takes 1/(1/6) = 6
 * rolls).
 * * 3. Structuring EV DP (Top-Down):
 * -> E[state] = SUM( P(transition) * (cost_of_transition + E[next_state]) )
 * -> CRITICAL: Always calculate Expected Value starting from the END
 * and working backwards to the START. Base case = target state (returns 0).
 * * ------------------------------------------
 * GAME THEORY (Combinatorial Games)
 * ------------------------------------------
 * 1. The Golden Rules of Winning/Losing States:
 * -> A state is a WINNING state if there is AT LEAST ONE move to a LOSING
 * state.
 * -> A state is a LOSING state if ALL possible moves lead to a WINNING state.
 * -> Base Case: If it's your turn and you have no moves left, it's a LOSING
 * state.
 * * 2. Standard DP Template for Games:
 * bool can_win(state) {
 * if (no_moves) return false;
 * if (memo[state] != -1) return memo[state];
 * for (move : valid_moves) {
 * // If we can force the opponent into a state where they CANNOT win
 * if (!can_win(next_state)) return memo[state] = true;
 * }
 * return memo[state] = false;
 * }
 * * 3. Game of Nim (The only math formula you need):
 * -> Setup: N piles of stones. A player can remove any number of stones from
 * exactly 1 pile.
 * -> Trick: Calculate the XOR sum of all pile sizes (S = p1 ^ p2 ^ ... ^ pN).
 * -> If S == 0: The second player guarantees a win (Losing state for current).
 * -> If S != 0: The first player guarantees a win (Winning state for current).
 */
// ==========================================
// 7. FAST MATRIX EXPONENTIATION
// ==========================================
template <typename T> struct Matrix {
  vector<vector<T>> mat;
  int n, m;

  // Constructors
  Matrix(int _n, int _m) : n(_n), m(_m) { mat.assign(n, vector<T>(m, 0)); }

  Matrix(vector<vector<T>> a) {
    mat = a;
    n = a.size();
    m = a[0].size();
  }

  // Makes the identity matrix (1s on the main diagonal)
  void makeIdentity() {
    for (int i = 0; i < min(n, m); i++) {
      mat[i][i] = 1;
    }
  }

  // Optimized Matrix Multiplication
  Matrix operator*(const Matrix &b) const {
    assert(m == b.n); // Inner dimensions must match
    Matrix res(n, b.m);
    for (int i = 0; i < n; i++) {
      for (int k = 0; k < m; k++) {
        if (mat[i][k] == 0)
          continue; // Skip zero multipliers
        for (int j = 0; j < b.m; j++) {
          res.mat[i][j] = (res.mat[i][j] + mat[i][k] * b.mat[k][j]) % MOD;
        }
      }
    }
    return res;
  }

  // O(log p) Matrix Exponentiation
  Matrix power(ll p) const {
    assert(n == m); // Must be a square matrix to exponentiate
    Matrix res(n, n);
    res.makeIdentity();
    Matrix base = *this;

    while (p > 0) {
      if (p & 1)
        res = res * base;
      base = base * base;
      p >>= 1;
    }
    return res;
  }

  // Debug printing
  void print() const {
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        cout << mat[i][j] << (j == m - 1 ? "" : " ");
      }
      cout << '\n';
    }
  }
};
// ==========================================
// 8. GEOMETRIC PROGRESSION (Modulo)
// ==========================================

// Calculates: (1 + r + r^2 + ... + r^{n-1}) % m
// Runs in O(log n) time. Safe from modular inverse traps.
ll modGeoSum(ll r, ll n, ll m) {
  // Base cases
  if (n == 0)
    return 0;
  if (n == 1)
    return 1 % m;

  // Divide the problem in half
  ll half = modGeoSum(r, n / 2, m);

  // Combine: S(n) = S(n/2) + r^(n/2) * S(n/2)
  ll res = (half + half * modpow(r, n / 2, m)) % m;

  // If n is odd, we missed the very last term (r^{n-1}), so add it
  if (n % 2 == 1) {
    res = (res + modpow(r, n - 1, m)) % m;
  }

  return res;
}
} // namespace CPMath

void solve() {
  ll n, m;

  // Read until End of File
  while (cin >> n >> m) {
    // Edge case 1: 0 never divides anything (except 0, but n! is at least 1)
    if (m == 0) {
      cout << m << " does not divide " << n << "!\n";
      continue;
    }

    // Edge case 2: If m <= n, it's guaranteed to be in the factorial
    if (m <= n) {
      cout << m << " divides " << n << "!\n";
      continue;
    }

    ll temp_m = m;
    bool divides = true;

    // Use the primes precomputed by your sieve()
    for (int i = 0; i < (int)CPMath::primes.size(); ++i) {
      ll p = CPMath::primes[i];

      // We only need to check primes up to sqrt(temp_m)
      if (p * p > temp_m)
        break;

      if (temp_m % p == 0) {
        ll required_count = 0;

        // Count how many times this prime goes into m
        while (temp_m % p == 0) {
          required_count++;
          temp_m /= p;
        }

        // Use your template's Legendre's Formula to check n!
        if (CPMath::vpFactorial(n, p) < required_count) {
          divides = false;
          break; // Stop checking immediately if it fails
        }
      }
    }

    // If temp_m > 1 after the loop, it is a prime strictly greater than its
    // sqrt
    if (divides && temp_m > 1) {
      // Again, use your template! (Though mathematically, this just checks n >=
      // temp_m)
      if (CPMath::vpFactorial(n, temp_m) < 1) {
        divides = false;
      }
    }

    if (divides) {
      cout << m << " divides " << n << "!\n";
    } else {
      cout << m << " does not divide " << n << "!\n";
    }
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  // Initialize your template's sieve to generate the primes list!
  // Note: For this specific problem, you can safely lower MAXN in your
  // template to 100000 (since max M is 2^31, sqrt(2^31) is ~46340) to make it
  // run instantly.
  CPMath::sieve();

  solve();

  return 0;
}
