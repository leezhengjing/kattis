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

void solve() {
  // cin.ignore(numeric_limits<streamsize>::max(), '\n');
  string s;
  cin >> s;

  int n = s.size();

  vi blue_positive(n);
  vi red_positive(n);

  for (int i = 0; i < n; ++i) {
    if (s[i] == 'B') {
      blue_positive[i] = 1;
      red_positive[i] = -1;
    } else {
      blue_positive[i] = -1;
      red_positive[i] = 1;
    }
  }

  // first kadane pass, for longest blue

  int max_sofar = 0;

  int start = 0, end = 0;
  int curr = 0;
  for (int right = 0; right < n; ++right) {
    curr += blue_positive[right];
    if (curr > max_sofar) {
      max_sofar = curr;
      end = right;
    }

    if (curr < 0) {
      curr = 0;
      start = right + 1;
    }
  }

  int second_max_sofar = 0;
  int second_start = 0, second_end = 0;
  curr = 0;
  for (int right = 0; right < n; ++right) {
    curr += red_positive[right];
    if (curr > second_max_sofar) {
      second_max_sofar = curr;
      second_end = right;
    }

    if (curr < 0) {
      curr = 0;
      second_start = right + 1;
    }
  }

  if (max_sofar > second_max_sofar) {
    cout << start + 1 << " " << end + 1 << "\n";
  } else if (max_sofar < second_max_sofar) {
    cout << second_start + 1 << " " << second_end + 1 << "\n";
  } else {
    if (start < second_start) {
      cout << start + 1 << " " << end + 1 << "\n";
    } else if (start > second_start) {
      cout << second_start + 1 << " " << second_end + 1 << "\n";
    } else {
      if (end < second_end) {
        cout << start + 1 << " " << end + 1 << "\n";
      } else {
        cout << second_start + 1 << " " << second_end + 1 << "\n";
      }
    }
  }
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
