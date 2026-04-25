
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

int global_count = 0;
bool first_found = false;

void dfs(vector<int> &path, vector<int> &res, vector<bool> &visited,
         const vector<vector<bool>> &hideous, int N) {
  if (path.size() == N) {
    ++global_count;

    if (!first_found) {
      res = path;
      first_found = true;
    }

    return;
  }

  for (int i = 0; i < N; ++i) {
    if (visited[i])
      continue;
    if (!path.empty()) {
      if (hideous[path.back()][i]) {
        continue;
      }
    }

    visited[i] = true;
    path.emplace_back(i);
    dfs(path, res, visited, hideous, N);
    path.pop_back();
    visited[i] = false;
  }
}

void solve() {
  // cin.ignore(numeric_limits<streamsize>::max(), '\n');
  int N;
  cin >> N;

  vector<string> preference(N);
  map<string, int> s_to_i;

  for (int i = 0; i < N; ++i) {
    cin >> preference[i];
    s_to_i[preference[i]] = i;
  }

  vector<vector<bool>> hideous(N, vector<bool>(N, false));
  int M;
  cin >> M;

  for (int i = 0; i < M; ++i) {
    string a, b;
    cin >> a >> b;

    int u = s_to_i[a];
    int v = s_to_i[b];
    hideous[u][v] = true;
    hideous[v][u] = true;
  }

  vector<int> path;
  vector<int> res;
  vector<bool> visited(N, false);
  dfs(path, res, visited, hideous, N);

  cout << global_count << "\n";

  first_found = false;
  global_count = 0;

  cout << preference[res[0]];
  for (int i = 1; i < N; ++i) {
    cout << " " << preference[res[i]];
  }

  cout << "\n";
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
