#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> ii;
typedef vector<ii> vii;

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
  int n;
  cin >> n;

  cin.ignore(numeric_limits<streamsize>::max(), '\n');

  vi arr = get_words<int>();
  arr.erase(remove(arr.begin(), arr.end(), 0), arr.end());

  vll prefix_sum(n, 0);
  vll suffix_sum(n, 0);

  for (int i = 1; i < n; ++i) {
    prefix_sum[i] = prefix_sum[i - 1] + arr[i - 1] * i;
  }

  for (int i = n - 2; i >= 0; --i) {
    suffix_sum[i] = suffix_sum[i + 1] + arr[i] * (i + 2);
  }

  ll res = -1e20;

  for (int i = 0; i < n; ++i) {
    res = max(prefix_sum[i] + suffix_sum[i], res);
  }

  cout << res << endl;
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
