
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
  int n, k;
  cin >> n >> k;
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  const int MAX_TIME = 2e5;
  vi arr(MAX_TIME, 0);

  int curr;
  for (int i = 0; i < n; ++i) {
    cin >> curr;
    arr[curr]++;
    arr[curr + 1000]--;
  }

  int res = 0;
  int sofar = 0;
  for (int i = 0; i < MAX_TIME; ++i) {
    sofar += arr[i];
    res = max(res, sofar);
  }

  cout << (res + k - 1) / k << endl;
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
