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

const ll INF = 1e18;

ll AM[205][205];

struct Lecture {
  int campus;
  int start;
  int end;
};

bool compareLectures(const Lecture &a, const Lecture &b) {
  return a.start < b.start;
}

void solve() {
  // cin.ignore(numeric_limits<streamsize>::max(), '\n');
  int C, L;
  cin >> C >> L;

  for (int i = 0; i < C; ++i) {
    for (int j = 0; j < C; ++j) {
      if (i == j)
        AM[i][j] = 0;
      else
        AM[i][j] = INF;
    }
  }

  int combinations = C * (C - 1) / 2;

  for (int i = 0; i < combinations; ++i) {
    int x, y, t;
    cin >> x >> y >> t;

    AM[x][y] = t;
    AM[y][x] = t;
  }

  // Floyd warshall
  for (int k = 0; k < C; ++k) {
    for (int i = 0; i < C; ++i) {
      for (int j = 0; j < C; ++j) {
        // if (AM[i][k] != INF && AM[k][j] != INF)
        AM[i][j] = min(AM[i][j], AM[i][k] + AM[k][j]);
      }
    }
  }

  vector<Lecture> lectures(L);
  for (int i = 0; i < L; ++i) {
    cin >> lectures[i].campus >> lectures[i].start >> lectures[i].end;
  }

  sort(lectures.begin(), lectures.end(), compareLectures);

  // dp[i] = max lecs attended ending with lec i;
  vi dp(L, 1);
  int res = 1;

  for (int i = 0; i < L; ++i) {
    for (int j = 0; j < i; ++j) {
      int edge = AM[lectures[j].campus][lectures[i].campus];

      if (lectures[j].end + edge <= lectures[i].start) {
        dp[i] = max(dp[i], dp[j] + 1);
      }
    }
    res = max(res, dp[i]);
  }

  cout << res << "\n";
}

int main() {
  fast_io();

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
