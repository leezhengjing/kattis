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

template <typename T> vector<T> get_words(bool flush = false) {
  if (flush) {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
  }
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
  int d, U;
  cin >> d >> U;
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  set<int> s;
  deque<ii> dq;
  for (int i = 1; i <= U; ++i) {
    s.insert(s.end(), i);
  }

  for (int i = 1; i <= U; ++i) {
    vector<string> line = get_words<string>();
    if (!dq.empty() && dq.front().first == i) {
      s.insert(dq.front().second);
      dq.pop_front();
    }
    if (line[0] == "a") {
      int to_remove = *s.begin();
      cout << to_remove << endl;
      s.erase(to_remove);
    } else if (line[0] == "r") {
      int index = stoi(line[1]);
      dq.emplace_back(i + d, index);
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
