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

int N;
int arr[1000];
int memo[1000][1000];

int dfs(int start_index, int last_jump) {
  if (start_index == N - 1) {
    return 0;
  }

  if (memo[start_index][last_jump] != -1) {
    return memo[start_index][last_jump];
  }
  int res = 1000000000;
  if (start_index + last_jump + 1 <= N - 1) {
    res = min(res, arr[start_index + last_jump + 1] +
                       dfs(start_index + last_jump + 1, last_jump + 1));
  }
  if (start_index - last_jump >= 0) {
    res = min(res, arr[start_index - last_jump] +
                       dfs(start_index - last_jump, last_jump));
  }
  memo[start_index][last_jump] = res;

  return res;
}

void solve() {
  // cin.ignore(numeric_limits<streamsize>::max(), '\n');
  cin >> N;
  memset(memo, -1, sizeof(memo));
  for (int i = 0; i < N; ++i) {
    cin >> arr[i];
  }
  int res = dfs(1, 1) + arr[1];
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
