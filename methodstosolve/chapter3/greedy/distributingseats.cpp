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
#define REP(i, s, t) for (int i = (s); i < (t); ++i)

template <class T> T read() {
  T v;
  std::cin >> v;
  return v;
}

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
  int n, r, c;
  cin >> n >> r >> c;

  vvi passengers(n + 1);
  for (int i = 0; i < n; ++i) {
    int curr_r, curr_c, curr_dist;
    cin >> curr_r >> curr_c >> curr_dist;

    int min_r = max(1, curr_r - curr_dist);
    int max_r = min(n, curr_r + curr_dist);
    passengers[min_r].push_back(max_r);
  }

  int res = 0;

  priority_queue<int, vi, greater<int>> pq;
  for (int row = 1; row <= n; ++row) {
    for (auto end_row : passengers[row]) {
      pq.push(end_row);
    }

    while (!pq.empty() && pq.top() < row) {
      pq.pop();
    }

    int seats_remaining = c;
    while (!pq.empty() && seats_remaining > 0) {
      res++;
      seats_remaining--;
      pq.pop();
    }
  }

  cout << res << "\n";
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
