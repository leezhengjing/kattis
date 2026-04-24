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

bool customCompare(const ii &a, const ii &b) {
  if (a.first != b.first) {
    return a.first < b.first;
  }
  return a.second > b.second;
}

void solve() {
  // cin.ignore(numeric_limits<streamsize>::max(), '\n');
  int n;
  cin >> n;

  int start_x, start_y, end_x, end_y;
  cin >> start_x >> start_y >> end_x >> end_y;

  ii start = {start_x, start_y};
  ii end = {end_x, end_y};

  if (start_x > end_x) {
    swap(start, end);
  }
  bool is_lis = start.second < end.second;

  vii errands; // .first = x, .second = y;

  for (int i = 0; i < n; ++i) {
    int curr_x, curr_y;
    cin >> curr_x >> curr_y;
    if (start.first <= curr_x && curr_x <= end.first &&
        min(start.second, end.second) <= curr_y &&
        curr_y <= max(start.second, end.second)) {
      errands.push_back({curr_x, curr_y});
    }
    // cin >> errands[i].first >> errands[i].second;
  }

  if (is_lis) {
    sort(errands.begin(), errands.end());
  } else {
    sort(errands.begin(), errands.end(), customCompare);
  }

  vi y_coords;
  for (auto &[x, y] : errands) {
    // cout << "x: " << x << "y: " << y << "\n";
    y_coords.push_back(y);
  }

  vi tails;

  if (is_lis) {
    for (int i = 0; i < errands.size(); ++i) {
      int val = y_coords[i];

      if (tails.empty() || val >= tails.back()) {
        tails.push_back(val);
      }

      auto it = upper_bound(tails.begin(), tails.end(), val);

      if (it != tails.end()) {
        *it = val;
      }
    }

  } else {
    for (int i = 0; i < errands.size(); ++i) {
      int val = y_coords[i];

      if (tails.empty() || val <= tails.back()) {
        tails.push_back(val);
      }
      auto it = upper_bound(tails.begin(), tails.end(), val, greater<int>());

      if (it != tails.end()) {
        *it = val;
      }
    }
  }

  cout << tails.size() << "\n";
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
