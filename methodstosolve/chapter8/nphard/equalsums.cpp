#include <bits/stdc++.h>
// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/tree_policy.hpp>
using namespace std;
// using namespace __gnu_pbds;

typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
// typedef tuple<int, ll, ll> edge;
typedef tuple<int, ll, ll, ll> edge;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<vi> vvi;

#define LSOne(S) ((S) & -(S))
// int two_pow_p1 = LSOne(mask);
// int p1 = __builtin_ctz(two_pow_p1);
#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define sz(x) (int)(x).size()

const ll INF = 1e18;
template <class T> T read() {
  T v;
  std::cin >> v;
  return v;
}

void fast_io() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
}

const int MAX = 2e6 + 5;

void solve(int tc) {
  int n;
  cin >> n;

  vi arr(n);
  int total = 0;
  for (int i = 0; i < n; ++i) {
    cin >> arr[i];
  }

  map<int, int> seen;

  cout << "Case #" << tc << ":\n";

  int total_subsets = 1 << n;

  for (int i = 1; i < total_subsets; ++i) {
    ll curr = 0;
    for (int j = 0; j < n; ++j) {
      if ((i >> j) & 1) {
        curr += arr[j];
      }
    }

    if (seen.count(curr)) {
      bool first = true;
      int mask = seen[curr];
      for (int j = 0; j < arr.size(); ++j) {
        if ((mask >> j) & 1) {
          if (!first)
            cout << " ";
          cout << arr[j];
          first = false;
        }
      }
      cout << "\n";

      first = true;
      for (int j = 0; j < arr.size(); ++j) {
        if ((i >> j) & 1) {
          if (!first)
            cout << " ";
          cout << arr[j];
          first = false;
        }
      }
      cout << "\n";

      return;
    }

    seen[curr] = i;
  }

  cout << "Impossible\n";
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;

  for (int i = 1; i <= t; ++i) {
    solve(i);
  }

  return 0;
}
