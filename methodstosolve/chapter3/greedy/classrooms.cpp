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

int n, k;

struct CustomCmp {
  bool operator()(const ii &a, const ii &b) const {
    if (a.second != b.second) {
      return a.second < b.second;
    }
    return a.first < b.first;
  }
};

void solve() {
  cin >> n >> k;

  vii activities(n);
  for (int i = 0; i < n; ++i) {
    int start, end;
    cin >> start >> end;
    activities[i] = {start, end};
  }

  CustomCmp cmp;
  sort(activities.begin(), activities.end(), cmp);

  multiset<int> room_end_times;

  int res = 0;
  for (const auto &activity : activities) {
    auto it = room_end_times.lower_bound(activity.first);

    if (it == room_end_times.begin()) {
      if (room_end_times.size() < k) {
        room_end_times.insert(activity.second);
        res++;
      }
    } else {
      --it;
      room_end_times.erase(it);
      room_end_times.insert(activity.second);
      res++;
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
