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
const int MOD = 1e9 + 7;

void fast_io() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
}
// Helper function: extracts digits and counts them in a size-10 array
// vector<int> get_digit_counts(long long n) {
//     vector<int> counts(10, 0);
//     if (n == 0) {
//         counts[0] = 1;
//         return counts;
//     }
//
//     while (n > 0) {
//         counts[n % 10]++;
//         n /= 10;
//     }
//     return counts;
// }
//
// struct Result {
//     long long x, y, p;
// };
//
// void solve() {
//     long long a, b;
//     if (!(cin >> a >> b)) return;
//
//     vector<Result> results;
//
//     // Test all pairs x <= y
//     for (long long x = a; x <= b; ++x) {
//
//         // Count digits for 'x'
//         vector<int> freq_x = get_digit_counts(x);
//
//         for (long long y = x; y <= b; ++y) {
//             long long p = x * y;
//
//             // Count digits for 'y' and the product 'p'
//             vector<int> freq_y = get_digit_counts(y);
//             vector<int> freq_p = get_digit_counts(p);
//
//             bool is_match = true;
//
//             // Compare the arrays: does x + y perfectly match p for every
//             digit? for (int i = 0; i < 10; ++i) {
//                 if (freq_x[i] + freq_y[i] != freq_p[i]) {
//                     is_match = false;
//                     break;
//                 }
//             }
//
//             if (is_match) {
//                 results.push_back({x, y, p});
//             }
//         }
//     }
//
//     // Output formatting
//     cout << results.size() << " digit-preserving pair(s)\n";
//     for (const auto& res : results) {
//         cout << "x = " << res.x << ", y = " << res.y << ", xy = " << res.p <<
//         "\n";
//     }
// }

ll get_freq_mask(ll n) {
  if (n == 0)
    return 1;
  ll mask = 0;

  while (n > 0) {
    ll digit = n % 10;
    mask += (1ULL << (digit * 4));
    n /= 10;
  }
  return mask;
}

struct Result {
  ll x, y, p;
};

void solve() {
  int A, B;
  cin >> A >> B;

  vll mask(B + 1);

  for (ll i = A; i <= B; ++i) {
    mask[i] = get_freq_mask(i);
  }

  vector<Result> res;

  for (ll x = A; x * x <= B; ++x) {
    for (ll y = x; x * y <= B; ++y) {
      ll p = x * y;

      if (mask[x] + mask[y] == mask[p]) {
        res.push_back({x, y, p});
      }
    }
  }

  cout << res.size() << " digit-preserving pair(s)\n";
  ;
  for (const auto &r : res) {
    cout << "x = " << r.x << ", y = " << r.y << ", xy = " << r.p << "\n";
  }
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
