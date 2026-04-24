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
template <typename T> vector<T> get_words() {
  string line;
  getline(std::cin, line);
  istringstream ss{line};
  ss >> boolalpha;
  vector<T> v;
  copy(istream_iterator<T>{ss}, istream_iterator<T>{}, back_inserter(v));
  return v;
}

int n;
void solve() {
  // cin.ignore(numeric_limits<streamsize>::max(), '\n');
  if (n == 0)
    return;

  vi arr(n);
  for (int i = 0; i < n; ++i) {
    cin >> arr[i];
  }

  // reconstructing the LIS... parent array doesnt work, i need the
  // lexicographically earliest
  //

  vi tails;

  // arr = [1, 25, 2, 3]; n = 4;
  // no. of operations = 0 + 1 + 2 + 3 = 6
  //
  // n = 10^5 , no of operatioosn = 10^10 (too slow) <= 10^8
  // no. of operations = 0 + 1 + 2 + 3 + ..... + 9999 = n/2 (n + 1) = O(n^2)
  // dp = [1 , 2 , 2 , 3]
  // dp[i] is the length of longest subsequence ending at index i inclusive of
  //
  //
  // k <= n;
  // O(n log k); == O (n log n) = O (10^6 * log(10^5) = )
  // log base 2
  //
  // 2^10 = 1024
  //
  // 2 ^ 20 = 1024 * 1024 = 10 ^ 3 * 10 ^ 3 = 10^6
  //
  // the i-th element
  //
  vi tail_indices;
  vi parent(n, -1);

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
      parent[i] = tail_indices[dist - 1];
    }
  }

  cout << tails.size();

  vi res;

  int curr = tail_indices.back();

  while (curr != -1) {
    res.push_back(arr[curr]);
    curr = parent[curr];
  }

  reverse(res.begin(), res.end());

  for (int x : res) {
    cout << " " << x;
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
