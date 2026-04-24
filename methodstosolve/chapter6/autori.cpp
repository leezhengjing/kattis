#include <bits/stdc++.h>

// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/tree_policy.hpp>
using namespace std;
// using namespace __gnu_pbds;

typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef tuple<int, ll, ll> edge;
// typedef tuple<int, ll, ll, ll> edge;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<vi> vvi;

#define LSOne(S) ((S) & -(S))
// int two_pow_p1 = LSOne(mask);
// int p1 = __builtin_ctz(two_pow_p1);
#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define sz(x) (int)(x).size()

const ll INF = 1e18;

void fast_io() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
}

void solve() {
  string s;
  cin >> s;
  for (char c : s) {
    if (isupper(c))
      cout << c;
  }
  // string s;
  // if (cin >> s) {
  //   // 1. Load the string into a stringstream
  //   stringstream ss(s);
  //   string word;
  //   string result = "";
  //
  //   // 2. Read from the stream into 'word', stopping at every '-'
  //   while (getline(ss, word, '-')) {
  //     // 3. Grab the first character of the parsed word
  //     result += word[0];
  //   }
  //
  //   cout << result << "\n";
  // }
  cout << "\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;

  while (t--) {
    solve();
  }

  return 0;
}
