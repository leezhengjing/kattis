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
  // cin.ignore(numeric_limits<streamsize>::max(), '\n');

  string line;
  while (getline(cin, line)) {
    if (line.empty())
      continue;

    stringstream ss(line);
    ss >> boolalpha;
    vector<int> arr;
    copy(istream_iterator<int>{ss}, istream_iterator<int>{},
         back_inserter(arr));

    unordered_set<int> set;
    int n = arr[0];
    for (int i = 1; i < n; ++i) {
      int diff = abs(arr[i] - arr[i + 1]);
      if (diff < n) {
        set.insert(diff);
      }
    }
    if (set.size() == n - 1) {
      cout << "Jolly" << endl;
    } else {
      cout << "Not jolly" << endl;
    }
  }
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
