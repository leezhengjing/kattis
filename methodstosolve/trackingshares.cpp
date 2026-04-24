#include <bits/stdc++.h>
#include <functional>
using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> ii;
typedef vector<ii> vii;

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
  int C;
  cin >> C;
  vi shares(365 + 1, 0);
  unordered_set<int> records;
  for (int i = 0; i < C; ++i) {
    int K;
    cin >> K;
    vii curr_shares;
    for (int j = 0; j < K; ++j) {
      int N, D;
      cin >> N >> D;
      curr_shares.push_back({D, N});
    }
    sort(curr_shares.begin(), curr_shares.end());
    for (int k = 0; k < curr_shares.size(); ++k) {
      int curr_d = curr_shares[k].first;
      int curr_n = curr_shares[k].second;
      if (k > 0) {
        curr_n -= curr_shares[k - 1].second;
      }
      records.insert(curr_d);
      shares[curr_d] += curr_n;
    }
  }

  int accum = 0;

  vi res;
  for (int i = 0; i <= shares.size(); ++i) {
    accum += shares[i];
    if (records.count(i)) {
      res.push_back(accum);
    }
  }

  for (int i = 0; i < res.size(); ++i) {
    cout << res[i] << (i == res.size() - 1 ? "" : " ");
  }
  cout << endl;
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
