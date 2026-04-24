#include <bits/stdc++.h>
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

struct Trip {
  ll finish_time;
  int net_count;
  int index;
};

struct CompareTrip {
  bool operator()(const Trip &a, const Trip &b) {
    if (a.finish_time != b.finish_time) {
      return a.finish_time > b.finish_time;
    }
    return a.net_count > b.net_count;
  };
};

void solve() {
  int n, k;
  cin >> n >> k;
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  //
  vi arr;
  for (int i = 0; i < n; ++i) {
    int t;
    cin >> t;
    arr.push_back(t);
  }

  sort(arr.begin(), arr.end());

  priority_queue<Trip, vector<Trip>, CompareTrip> pq;

  for (int i = 0; i < min(n, k); ++i) {
    pq.push({arr[i], 5, i});
  }

  ll res = 0;

  while (n > 0) {
    Trip curr = pq.top();
    res = curr.finish_time;
    pq.pop();
    n -= curr.net_count;
    pq.push({curr.finish_time + arr[curr.index] * 2, 4, curr.index});
  }

  cout << res << endl;
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;

  while (t--) {
    // code here
    solve();
  }

  return 0;
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
