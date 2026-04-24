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
  vector<int> arr;
  for (int i = 0; i < 4; ++i) {
    double val;
    cin >> val;
    int val_to_int = val * 100;
    arr.push_back(val_to_int);
  }

  double target;
  cin >> target;
  ll target_to_int = target * 100;
  sort(arr.begin(), arr.end());
  ll lowest_sum = 0;
  for (int i = arr.size() - 1; i > 0; --i) {
    lowest_sum += arr[i];
  }

  if (lowest_sum < target_to_int * 3) {
    cout << "infinite" << "\n";
    return;
  }

  lowest_sum -= arr[3];

  ll best_sum = target_to_int * 3;

  ll left = arr[0], right = best_sum - lowest_sum;

  if (right < left) {
    cout << "impossible" << "\n";
    return;
  }
  cout << fixed << setprecision(2);
  cout << (double)right / 100.00 << "\n";
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
