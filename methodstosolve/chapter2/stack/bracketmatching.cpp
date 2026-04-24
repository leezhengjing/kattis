#include <bits/stdc++.h>
// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/tree_policy.hpp>
using namespace std;
// using namespace __gnu_pbds;

typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef tuple<int, ll, ll> edge; // For MaxFlow
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<vi> vvi;

#define LSOne(S) ((S) & -(S))
// int two_pow_p1 = LSOne(mask);
// int p1 = __builtin_ctz(two_pow_p1);
#define REP(i, s, t) for (int i = (s); i < (t); ++i)

const ll INF = 1e18;
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

  int n;
  cin >> n;
  string s;
  cin >> s;

  unordered_map<char, char> open_to_close = {
      {'(', ')'},
      {'{', '}'},
      {'[', ']'},
  };

  vector<char> arr;

  for (auto character : s) {
    if (arr.empty()) {
      if (open_to_close.count(character)) {
        arr.push_back(character);
      } else {
        cout << "Invalid\n";
        return;
      }
    } else {
      if (open_to_close.count(character)) {
        arr.push_back(character);
      } else {
        if (open_to_close[arr.back()] == character) {
          arr.pop_back();
        } else {
          cout << "Invalid\n";
          return;
        }
      }
    }
  }

  if (arr.size() > 0) {
    cout << "Invalid\n";
  } else {
    cout << "Valid\n";
  }
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
