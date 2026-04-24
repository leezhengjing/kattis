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

const double EPS = 1e-9;

int n;

void solve() {
  // cin.ignore(numeric_limits<streamsize>::max(), '\n');
  if (n == 0)
    return;

  vi time(n);
  vi profit(n);
  for (int i = 0; i < n; ++i) {
    double p;
    cin >> time[i] >> p;
    profit[i] = p * 100 + (p >= 0 ? 0.5 : -0.5);
  }

  int res = 0;

  int start_res = -1, end_res = -1;
  int start = 0;
  int curr = 0;

  for (int i = 0; i < n; ++i) {
    if (i == start) {
      curr -= 8;
    } else {
      curr -= 8 * (time[i] - time[i - 1]);
    }

    if (curr <= -8) {
      start = i;
      curr = -8;
    }
    curr += profit[i];

    if (curr > res) {
      res = curr;
      start_res = start;
      end_res = i;
    } else if (curr == res && res > 0) {
      int curr_duration = time[i] - time[start];
      int best_duration = time[end_res] - time[start_res];

      if (curr_duration < best_duration) {
        start_res = start;
        end_res = i;
      }
    }
  }

  if (res <= 0) {
    cout << "no profit\n";
    return;
  }

  cout << fixed << setprecision(2);
  cout << (double)res / 100.0 << " " << time[start_res] << " " << time[end_res]
       << "\n";
}

int main() {
  fast_io();

  int t = 150;
  // cin >> t;

  while (cin >> n && n != 0) {
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
