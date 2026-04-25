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

const double EPS = 1e-9;

bool is_valid(const double &mid, const vector<double> &arr, const int &F) {
  int count = 0;

  for (int i = 0; i < arr.size(); ++i) {
    count += (arr[i] + EPS) / mid;
  }
  return count >= F;
}

void solve() {
  // cin.ignore(numeric_limits<streamsize>::max(), '\n');
  int N, F;
  cin >> N >> F;
  vector<double> arr(N);
  double pi_d = M_PI;

  double left = 0.0, right = 0.0;

  for (int i = 0; i < N; ++i) {
    double r;
    cin >> arr[i];
    arr[i] = arr[i] * arr[i] * pi_d;
    if (arr[i] > right) {
      right = arr[i];
    }
  }

  for (int i = 0; i < 100; ++i) {
    double mid = left + (right - left) / 2.0;
    if (is_valid(mid, arr, F + 1)) {
      left = mid;
    } else {
      right = mid;
    }
  }

  cout << fixed << setprecision(9) << left << "\n";
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
