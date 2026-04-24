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

unordered_map<int, deque<int>> solutions;

void solve() {
  // cin.ignore(numeric_limits<streamsize>::max(), '\n');
  int query;
  cin >> query;
  deque<int> solution = solutions[query];
  for (int i = 0; i < query; ++i) {
    if (i == 0) {
      cout << solution[i];
    } else {
      cout << " " << solution[i];
    }
  }
  cout << "\n";
}

void precalculate() {
  for (int i = 1; i <= 13; ++i) {
    deque<int> q{i};
    for (int j = i - 1; j > 0; --j) {
      q.emplace_front(j);
      for (int k = j; k > 0; --k) {
        q.emplace_front(q.back());
        q.pop_back();
      }
    }
    solutions[i] = q;
  }
}

int main() {
  fast_io();
  precalculate();

  int t = 1;
  cin >> t;

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
