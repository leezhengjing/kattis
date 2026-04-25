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

const double INF = 1e18;
const double EPS = 1e-6;

void solve() {
  // cin.ignore(numeric_limits<streamsize>::max(), '\n');
  int N;
  cin >> N;

  vector<vii> AL(N + 1);
  vi indegree(N + 1, 0);
  vector<double> M_arr(N + 1);
  for (int i = 1; i <= N; ++i) {
    cin >> M_arr[i];
    int K;
    cin >> K;

    for (int j = 0; j < K; ++j) {
      int neighbor, weight;
      cin >> neighbor >> weight;
      AL[i].push_back({neighbor, weight});
      indegree[neighbor] += 1;
    }
  }

  vector<double> envelopes(N + 1, 0);

  queue<int> q;
  vi res(0);
  for (int i = 1; i <= N; ++i) {
    if (indegree[i] == 0) {
      q.push(i);
      envelopes[i] = INF;
    }
  }

  while (!q.empty()) {
    int node = q.front();
    q.pop();
    double incoming = envelopes[node];
    double capacity = M_arr[node];
    double actual_output = min(incoming, capacity);

    if (incoming >= capacity - EPS) {
      res.push_back(node);
      actual_output = capacity;
    }

    for (const auto &[neighbor, weight] : AL[node]) {
      envelopes[neighbor] += actual_output * (weight / 100.0);
      indegree[neighbor]--;
      if (indegree[neighbor] == 0) {
        q.push(neighbor);
      }
    }
  }

  sort(res.begin(), res.end());
  cout << res[0];
  for (int i = 1; i < res.size(); ++i) {
    cout << " " << res[i];
  }
  cout << "\n";
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
