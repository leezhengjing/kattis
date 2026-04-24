#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<vi> vvi;

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

class SegmentTree { // OOP style
private:
  int n; // n = (int)curr_gems.size()
  vi curr_gems;
  vi gemValues; // gem values, changed in type 2
  vvi st;       // freq counter of gems

  int l(int p) { return p << 1; }       // go to left child
  int r(int p) { return (p << 1) + 1; } // go to right child

  vi conquer(const vi &a, const vi &b) {
    vi res(6, 0);
    for (int i = 0; i < 6; ++i) {
      res[i] = a[i] + b[i];
    }
    return res;
  }

  void build(int p, int L, int R) { // O(n)
    if (L == R) {
      st[p][curr_gems[L]] = 1; // base case

    } else {
      int m = (L + R) / 2;
      build(l(p), L, m);
      build(r(p), m + 1, R);
      st[p] = conquer(st[l(p)], st[r(p)]);
    }
  }

  vi RQ(int p, int L, int R, int i, int j) { // O(log n)
    if (i > j)
      return vi(6, 0);
    if ((L >= i) && (R <= j)) {
      return st[p]; // found the segment
    }
    int m = (L + R) / 2;
    return conquer(RQ(l(p), L, m, i, min(m, j)),
                   RQ(r(p), m + 1, R, max(i, m + 1), j));
  }

  void update(int p, int L, int R, int idx, int old_type,
              int new_type) { // O(log n)
    if (L == R) {
      st[p][old_type]--;
      st[p][new_type]++;
      return;
    }
    int m = (L + R) / 2;
    if (idx <= m) {
      update(l(p), L, m, idx, old_type, new_type);
    } else {
      update(r(p), m + 1, R, idx, old_type, new_type);
    }

    st[p] = conquer(st[l(p)], st[r(p)]);
  }

public:
  SegmentTree(int sz) : n(sz), curr_gems(n), st(4 * n, vi(6, 0)) {}

  SegmentTree(const vi &initialA, const vi &gem_values)
      : SegmentTree((int)initialA.size()) {
    curr_gems = initialA;
    gemValues = gem_values;
    build(1, 0, n - 1);
  }

  void replace_gem(int index, int new_type) {
    int old_type = curr_gems[index];
    update(1, 0, n - 1, index, old_type, new_type);
    curr_gems[index] = new_type;
  }

  void update_gem_value(int change_index, int new_val) {
    gemValues[change_index] = new_val;
  }

  ll RQ(int i, int j) {
    vi arr = RQ(1, 0, n - 1, i, j);
    ll res = 0;
    for (int i = 0; i < 6; ++i) {
      res += (ll)arr[i] * gemValues[i];
    }
    return res;
  }
};

void solve() {
  int N, Q;
  cin >> N >> Q;
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  vi gem_values = get_words<int>();
  string s;
  getline(cin, s);
  vi arr;
  for (char c : s) {
    arr.push_back(c - '0' - 1);
  }
  SegmentTree st{arr, gem_values};

  for (int i = 0; i < Q; ++i) {
    vi line = get_words<int>();
    if (line[0] == 1) {
      st.replace_gem(line[1] - 1, line[2] - 1);
    } else if (line[0] == 2) {
      st.update_gem_value(line[1] - 1, line[2]);
    } else if (line[0] == 3) {
      cout << st.RQ(line[1] - 1, line[2] - 1) << endl;
    };
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
