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

struct CustomCmp {
  bool operator()(const pair<ll, ll> &a, const pair<ll, ll> &b) const {
    if (a.first * b.second != b.first * a.second) {
      return (a.first * b.second) < (b.first * a.second);
    }
    return a.first < b.first;
  }
};

void solve() {
  // cin.ignore(numeric_limits<streamsize>::max(), '\n');
  int F, B;
  cin >> F >> B;
  vll front(F, 0);
  vll back(B, 0);

  vector<pair<ll, ll>> pairs;

  for (int i = 0; i < F; ++i) {
    cin >> front[i];
  }
  for (int i = 0; i < B; ++i) {
    cin >> back[i];
  }

  CustomCmp cmp;
  for (int i = 0; i < F; ++i) {
    for (int j = 0; j < B; ++j) {
      pairs.push_back({front[i], back[j]});
    }
  }

  sort(pairs.begin(), pairs.end(), cmp);

  for (auto const &[front, back] : pairs) {
    cout << "(" << front << "," << back << ")" << "\n";
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
