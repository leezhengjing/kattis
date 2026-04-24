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

long long H_partial(long long previousHash, string &transaction) {
  long long v = previousHash;
  for (int i = 0; i < transaction.length(); i++) {
    v = (v * 31 + transaction[i]) % 1000000007;
  }
  return (v * 7) % 1000000007;
}
long long H(long long previousHash, string &transaction, long long token) {
  long long v = previousHash;
  for (int i = 0; i < transaction.length(); i++) {
    v = (v * 31 + transaction[i]) % 1000000007;
  }
  return (v * 7 + token) % 1000000007;
}
void solve() {
  // cin.ignore(numeric_limits<streamsize>::max(), '\n');
  ll previousHash;
  cin >> previousHash;
  string trans = "a";

  ll partial = H_partial(previousHash, trans);
  ll a_token = 0;
  ll a_hash = 0;

  for (ll t = 0; t <= 1000000006; ++t) {
    ll curr = (partial + t) % 1000000007;
    if (curr % 10000000 == 0) {
      a_token = t;
      a_hash = curr;
      break;
    }
  }

  ll b_partial = H_partial(a_hash, trans);
  ll b_token = 0;
  ll b_hash = 0;

  for (ll t = 0; t <= 1000000006; ++t) {
    ll curr = (b_partial + t) % 1000000007;
    if (curr % 10000000 == 0) {
      b_token = t;
      b_hash = curr;
      break;
    }
  }

  cout << trans << " " << a_token << "\n";
  cout << trans << " " << b_token << "\n";
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
