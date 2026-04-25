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
  int N;
  cin >> N;
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  float vt = 0, ct = 0, va = 0, vb = 0, vc = 0, ca = 0, cb = 0, cc = 0;
  for (int i = 0; i < N; ++i) {
    string line;
    getline(cin, line);
    if (line[0] == 'Y') {
      ++vt;
      if (line[1] == 'Y') {
        ++va;
      }
      if (line[2] == 'Y') {
        ++vb;
      }
      if (line[3] == 'Y') {
        ++vc;
      }
    } else {
      ++ct;
      if (line[1] == 'Y') {
        ++ca;
      }
      if (line[2] == 'Y') {
        ++cb;
      }
      if (line[3] == 'Y') {
        ++cc;
      }
    }
  }
  float vair = va / vt;
  float vbir = vb / vt;
  float vcir = vc / vt;

  float cair = ca / ct;
  float cbir = cb / ct;
  float ccir = cc / ct;

  if (vair < cair) {
    cout << (cair - vair) / cair * 100 << endl;
  } else {
    cout << "Not Effective" << endl;
  }
  if (vbir < cbir) {
    cout << (cbir - vbir) / cbir * 100 << endl;
  } else {
    cout << "Not Effective" << endl;
  }
  if (vcir < ccir) {
    cout << (ccir - vcir) / ccir * 100 << endl;
  } else {
    cout << "Not Effective" << endl;
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
