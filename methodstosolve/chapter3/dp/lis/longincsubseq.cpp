#include <bits/stdc++.h>
// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/tree_policy.hpp>
using namespace std;
// using namespace __gnu_pbds;

typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<vi> vvi;

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

int n;

void solve() {
  vll arr(n);
  for (int i = 0; i < n; ++i) {
    cin >> arr[i];
  }

  vll tails;
  vi tail_indices;
  vi parents(n, -1);

  for (int i = 0; i < n; ++i) {
    ll val = arr[i];

    auto it = lower_bound(tails.begin(), tails.end(), val);
    int dist = distance(tails.begin(), it);

    if (it == tails.end()) {
      tails.push_back(val);
      tail_indices.push_back(i);
    } else {
      *it = val;
      tail_indices[dist] = i;
    }

    if (dist > 0) {
      parents[i] = tail_indices[dist - 1];
    }
  }

  cout << tails.size() << "\n";

  vi res;
  int curr = tail_indices.back();
  while (curr != -1) {
    res.push_back(curr);
    curr = parents[curr];
  }

  reverse(res.begin(), res.end());

  cout << res[0];
  for (int i = 1; i < res.size(); ++i) {
    cout << " " << res[i];
  }
  cout << "\n";
}

int main() {
  fast_io();

  int t = 1;

  while (cin >> n) {
    // code here
    solve();
  }

  // reading input
  // read int: int n; cin >> n;
  // read line: string s; getline(cin, s);
  // read list/arr: vi arr(n); for(int i=0; i<n; ++i) cin >> arr[i];
  // eof reading: int n; while(cin >> n) { ... }

  return 0;
}
