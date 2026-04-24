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
int B;
vector<pair<double, double>> tax_bands;

void solve() {
  // cin.ignore(numeric_limits<streamsize>::max(), '\n');
  cin >> B;
  tax_bands.resize(B);

  double curr_boundary = 0;
  for (int i = 0; i < B; ++i) {
    double size, percent;
    cin >> size >> percent;
    curr_boundary += size;
    tax_bands[i] = {curr_boundary, percent / 100.0};
  }

  double P;
  cin >> P;
  int F;
  cin >> F;

  cout << fixed << setprecision(6);

  for (int i = 0; i < F; ++i) {
    double start_income, target;
    cin >> start_income >> target;

    double curr_gros_pos = start_income;
    double added_gross = 0;
    double remaining_needed = target;

    for (int b = 0; b < B; ++b) {
      if (remaining_needed <= 0)
        break;

      double boundary = tax_bands[b].first;
      double rate = tax_bands[b].second;

      if (curr_gros_pos >= boundary)
        continue;

      double gross_room = boundary - curr_gros_pos;

      double net_capacity = gross_room * (1.0 - rate);

      if (remaining_needed <= net_capacity) {
        added_gross += remaining_needed / (1.0 - rate);
        remaining_needed = 0;
      } else {
        added_gross += gross_room;
        remaining_needed -= net_capacity;
        curr_gros_pos = boundary;
      }
    }

    if (remaining_needed > EPS) {
      double rate = P / 100.0;
      double gross_needed = remaining_needed / (1.0 - rate);
      added_gross += gross_needed;
    }

    cout << added_gross << "\n";
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
