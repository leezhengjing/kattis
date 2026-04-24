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

void solve() {
  int N, K;

  cin >> N >> K;

  vi arr(N);
  for (int i = 0; i < N; ++i) {
    cin >> arr[i];
  }

  vi sorted_arr = arr;

  sort(sorted_arr.begin(), sorted_arr.end());

  unordered_map<int, int> val_to_group;

  int count = 0, group = 0;
  for (int i = 0; i < N; ++i) {
    if (count == K) {
      group++;
      count = 0;
    }
    int val = sorted_arr[i];
    count++;
    val_to_group[val] = group;
  }

  for (int i = 0; i < N; ++i) {
    arr[i] = val_to_group[arr[i]];
  }

  // for (auto val : arr) {
  //   cout << val << " ";
  // }

  vi tails;
  for (int i = 0; i < N; ++i) {
    int val = arr[i];

    auto it = upper_bound(tails.begin(), tails.end(), val);

    if (it == tails.end()) {
      tails.push_back(val);
    } else {
      *it = val;
    }
  }

  cout << N - tails.size() << "\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;

  while (t--) {
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
