#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> ii;
typedef vector<ii> vii;

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
  int t;
  cin >> t;
  for (int k = 0; k < t; ++k) {
    int N;
    cin >> N;
    vi red, blue;
    string s;
    for (int i = 0; i < N; ++i) {
      cin >> s;
      if (s.back() == 'R') {
        red.push_back(stoi(s));
      } else if (s.back() == 'B') {
        blue.push_back(stoi(s));
      }
    }
    sort(red.rbegin(), red.rend());
    sort(blue.rbegin(), blue.rend());

    int res = 0;

    for (int i = 0; i < min(blue.size(), red.size()); ++i) {
      res += red[i] + blue[i] - 2;
    }

    cout << "Case #" << k + 1 << ": " << res << endl;
  }
}

int main() {
  fast_io();

  int t = 1;

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
