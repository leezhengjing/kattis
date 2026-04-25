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

bool check_forward(const vi &a, const vi &b, int index) {
  for (int i = 0; i < a.size(); ++i) {
    if (a[i] != b[i + index]) {
      return false;
    }
  }
  return true;
}

void solve() {
  int n, m;
  cin >> n >> m;
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  vi initial = get_words<int>();
  initial.insert(initial.end(), initial.begin(), initial.end());
  vi test = get_words<int>();
  vi reversed_test(test.rbegin(), test.rend());

  for (int i = 0; i < initial.size() - test.size(); ++i) {
    if (check_forward(test, initial, i)) {
      cout << 1 << endl;
      return;
    }
  }
  for (int i = 0; i < initial.size() - test.size(); ++i) {
    if (check_forward(reversed_test, initial, i)) {
      cout << 1 << endl;
      return;
    }
  }
  cout << 0 << endl;
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
