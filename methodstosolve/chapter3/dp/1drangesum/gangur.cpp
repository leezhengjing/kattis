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

void solve() {
  // cin.ignore(numeric_limits<streamsize>::max(), '\n');
  string s;
  getline(cin, s);

  int n = s.size();

  vll prefix_right(n + 1, 0);
  vll suffix_left(n + 1, 0);

  for (int i = n - 1; i >= 0; --i) {
    if (s[i] == '<') {
      suffix_left[i]++;
    }
    suffix_left[i] += suffix_left[i + 1];
  }
  // for (int i = 1; i <= n; ++i) {
  //   if (s[i - 1] == '>')
  //     prefix_right[i]++;
  //   prefix_right[i] += prefix_right[i - 1];
  // }

  ll res = 0;
  for (int i = 0; i < n; ++i) {
    // if (s[i] == '<')
    //   res += prefix_right[i];
    if (s[i] == '>')
      res += suffix_left[i];
  }

  cout << res << "\n";
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
