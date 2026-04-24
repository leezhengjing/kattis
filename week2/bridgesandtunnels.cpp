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

template <class T> class UnionFind {
private:
  unordered_map<T, T> p;
  unordered_map<T, int> setSize;

public:
  T find(const T &x) {
    if (setSize.find(x) == setSize.end()) {
      setSize[x] = 1;
      p[x] = x;
    }
    T y = p.count(x) ? p[x] : x;
    if (y != x) {
      y = find(y);
      p[x] = y;
    }
    return y;
  }
  int sizeOfSet(T x) { return setSize[find(x)]; }

  void union_(const T &x, const T &y) {
    T root_x = find(x);
    T root_y = find(y);
    if (root_x == root_y)
      return;

    if (setSize[root_x] < setSize[root_y]) {
      p[root_x] = root_y;
      setSize[root_y] += setSize[root_x];
    } else {
      p[root_y] = root_x;
      setSize[root_x] += setSize[root_y];
    }
  }
};

void solve() {
  int n;
  cin >> n;
  UnionFind<string> uf;
  for (int i = 0; i < n; ++i) {
    string a, b;
    cin >> a >> b;
    uf.union_(a, b);
    cout << uf.sizeOfSet(a) << endl;
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;

  while (t--) {
    solve();
  }

  // reading input
  // read int: int n; cin >> n;
  // read line: string s; getline(cin, s);
  // read list/arr: vi arr(n); for(int i=0; i<n; ++i) cin >> arr[i];
  // eof reading: int n; while(cin >> n) { ... }

  return 0;
}
