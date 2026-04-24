#include <bits/stdc++.h>
// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/tree_policy.hpp>
using namespace std;
// using namespace __gnu_pbds;

typedef long long ll;
typedef vector<int> vi;
// using vi = vector<int>;
typedef vector<ll> vll;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<vi> vvi;
#define pb push_back

#define LSOne(S) ((S) & -(S))
// int two_pow_p1 = LSOne(mask);
// int p1 = __builtin_ctz(two_pow_p1);
#define REP(i, s, t) for (int i = (s); i < (t); ++i)

template <class T> T read() {
  T v;
  std::cin >> v;
  return v;
}

void fast_io() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
}

void solve() {
  int m, n;
  cin >> m >> n;

  vi R(m);
  int sum_R = 0;
  for (int i = 0; i < m; ++i) {
    cin >> R[i];
    sum_R += R[i];
  }

  vi C(n);
  int sum_C = 0;

  for (int i = 0; i < n; ++i) {
    cin >> C[i];
    sum_C += C[i];
  }

  if (sum_R != sum_C) {
    cout << "No\n";
    return;
  }

  for (int i = 0; i < m; ++i) {
    sort(C.begin(), C.end(), greater<int>());

    int ones_to_put = R[i];

    for (int j = 0; j < ones_to_put; ++j) {
      if (C[j] == 0) {
        cout << "No\n";
        return;
      }
      C[j]--;
    }
  }
  cout << "Yes\n";
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
