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

template <typename T> void put_words(const vector<T> &v) {
  if (!v.empty()) {
    copy(v.begin(), prev(v.end()), ostream_iterator<T>{cout, " "});
    cout << v.back();
  }
  cout << '\n';
}

void solve() {
  // cin.ignore(numeric_limits<streamsize>::max(), '\n');
  int n;
  char colon;
  if (!(cin >> n >> colon))
    return;

  vector<bool> seen(n, false);

  vi arr(n, 0);

  for (int i = 0; i < n; ++i) {
    cin >> arr[i];
  }

  for (int curr : arr) {
    for (int diff = 1; curr - diff >= 0 && curr + diff < n; ++diff) {
      int left = curr - diff;
      int right = curr + diff;

      if (seen[left] != seen[right]) {
        cout << "no" << "\n";
        return;
      }
    }
    seen[curr] = true;
  }

  cout << "yes" << "\n";
  return;
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;

  while (cin.peek() != EOF) {
    solve();
    cin >> ws;
  }

  // reading input
  // read int: int n; cin >> n;
  // read line: string s; getline(cin, s);
  // read list/arr: vi arr(n); for(int i=0; i<n; ++i) cin >> arr[i];
  // eof reading: int n; while(cin >> n) { ... }

  return 0;
}
