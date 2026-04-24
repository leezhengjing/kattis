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

#define LSOne(S) ((S) & -(S))
// int two_pow_p1 = LSOne(mask);
// int p1 = __builtin_ctz(two_pow_p1);

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
const int UPPER_BOUND = 1005;

int arr[UPPER_BOUND];

int N;

vector<__int128_t> curr_number;

int solve(int start_index) {
  // cin.ignore(numeric_limits<streamsize>::max(), '\n');

  if (start_index > N) {
    return 1;
  }

  __int128_t curr = 0;
  for (int d = 0; d < 10; ++d) {
    if (start_index == 1 && d == 0)
      continue;
    __int128_t next_number = curr_number[start_index - 1] * 10 + d;
    if (next_number % start_index == 0) {
      curr_number[start_index] = next_number;
      curr += solve(start_index + 1);
    }
  };

  return curr;
};

int main() {
  fast_io();

  // int t = 1;
  // cin >> t;

  // while (t--) {
  // code here
  //
  vi arr(1001, 0);
  for (int i = 1; i <= 1000; ++i) {
    curr_number.assign(1001, 0);
    N = i;
    int res = solve(1);
    arr[i] = res;
  }

  cout << "int arr[1001] = {\n";
  for (int i = 1; i <= 1000; ++i) {
    cout << arr[i] << ", ";
  }
  cout << "\n";
  cout << "};\n";
  // }

  // reading input
  // read int: int n; cin >> n;
  // read line: string s; getline(cin, s);
  // read list/arr: vi arr(n); for(int i=0; i<n; ++i) cin >> arr[i];
  // eof reading: int n; while(cin >> n) { ... }

  return 0;
}
