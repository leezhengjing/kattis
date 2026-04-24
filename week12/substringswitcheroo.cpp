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

void solve() {
  string A, B;
  cin >> A >> B;

  int n = A.length();

  string ans = "";

  for (int k = n; k > 0; --k) {
    set<vi> signatures_B;
    vi freq_counterB(26, 0);
    vi freq_counterA(26, 0);

    for (int i = 0; i < k; ++i) {
      freq_counterB[B[i] - 'a']++;
      freq_counterA[A[i] - 'a']++;
    }

    signatures_B.insert(freq_counterB);

    for (int i = k; i < n; ++i) {
      freq_counterB[B[i] - 'a']++;
      freq_counterB[B[i - k] - 'a']--;
      signatures_B.insert(freq_counterB);
    }

    if (signatures_B.count(freq_counterA)) {
      cout << A.substr(0, k) << "\n";
      return;
    }

    for (int i = k; i < n; ++i) {
      freq_counterA[A[i] - 'a']++;
      freq_counterA[A[i - k] - 'a']--;

      if (signatures_B.count(freq_counterA)) {
        cout << A.substr(i - k + 1, k) << "\n";
        return;
      }
    }
  }

  if (ans != "")
    cout << ans << "\n";
  else
    cout << "NONE\n";
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
