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
  int N;
  cin >> N;

  vi arr(N);
  unordered_map<int, vi> forward;
  unordered_map<int, vi> backward;

  for (int i = 0; i < N; ++i) {
    cin >> arr[i];

    forward[i - arr[i]].push_back(i);
    backward[i + arr[i]].push_back(i);
  }

  vector<bool> visited(N, false);
  queue<int> q;

  visited[0] = true;
  q.push(0);

  int res = 0;

  while (!q.empty()) {
    int curr_idx = q.front();
    q.pop();

    if (curr_idx > res) {
      res = curr_idx;
    }

    int target = curr_idx + arr[curr_idx];
    if (forward.count(target)) {
      for (int neighbor : forward[target]) {
        if (!visited[neighbor]) {
          q.push(neighbor);
          visited[neighbor] = true;
        }
      }
      forward.erase(target);
    }

    target = curr_idx - arr[curr_idx];

    if (backward.count(target)) {
      for (int neighbor : backward[target]) {
        if (!visited[neighbor]) {
          q.push(neighbor);
          visited[neighbor] = true;
        }
      }
      backward.erase(target);
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
