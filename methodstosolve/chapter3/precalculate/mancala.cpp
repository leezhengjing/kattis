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

const int total_count = 2000;
vvi results(total_count + 1, vi(81, 0));

void precompute() {
  vi bins(total_count + 1, 0);

  vi board(81, 0);
  int bin_idx = 1;
  for (int i = 1; i <= total_count; ++i) {
    int r = 1;

    while (board[r] != 0) {
      board[r]--;
      r++;
    }
    board[r] = r;

    results[i] = board;
    bin_idx = max(bin_idx, r);
    bins[i] = bin_idx;
  }
}

void solve() {
  int K, N;
  cin >> K >> N;
  int max_idx = 0;
  vi res = results[N];
  for (int i = 80; i >= 0; --i) {
    if (res[i] != 0) {
      max_idx = i;
      break;
    }
  }
  cout << max_idx << "\n";
  cout << res[1];
  for (int i = 2; i < max_idx; ++i) {
    if (i % 10 == 0) {

      cout << "\n";
      cout << res[i];
      continue;
    }
    cout << " " << res[i];
  }
  cout << "\n";
}

set<int, vi> answers;

int main() {
  fast_io();

  precompute();
  int T = 1;
  cin >> T;
  for (int t = 1; t <= T; ++t) {
    cout << t << " ";
    solve();
  }

  // reading input
  // read int: int n; cin >> n;
  // read line: string s; getline(cin, s);
  // read list/arr: vi arr(n); for(int i=0; i<n; ++i) cin >> arr[i];
  // eof reading: int n; while(cin >> n) { ... }

  return 0;
}
