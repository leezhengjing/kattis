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

int N, H;
int bottom[100000];
int top[100000];

void solve() {
  // cin.ignore(numeric_limits<streamsize>::max(), '\n');
  cin >> N >> H;

  for (int i = 0; i < N; ++i) {
    if (i % 2 == 0)
      cin >> bottom[i / 2];
    else
      cin >> top[i / 2];
  }

  sort(bottom, bottom + N / 2);
  sort(top, top + N / 2);

  int res_count = N;
  int res_levels = 0;
  for (int i = 1; i <= H; ++i) {
    int curr_count = (bottom + N / 2) - lower_bound(bottom, bottom + N / 2, i) +
                     (top + N / 2) - lower_bound(top, top + N / 2, H - i + 1);
    if (curr_count < res_count) {
      res_count = curr_count;
      res_levels = 1;
    } else if (curr_count == res_count) {
      res_levels++;
    }
  }

  cout << res_count << " " << res_levels << "\n";
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
