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

// brute force is guess each letter at each index.. = 4 guesses per index *
// length n = 4n; n = 10^4... 4 x 10 ^ 4 should be okay?
//
// okay it passes group 1 4 * n
// i need to do 2.45 * n... 2.45 guesses per index??
//
// can i do better... if i guess 3 times and all no, i dont need the 4th time...
// so i guess grou p2 is just try P I Z
//
// Maybe grp 3 is smth like try P/I, if not it will be Z/A. Then we start
// guessing the next index? but i dont think we can confirm just yet, like if it
// returns 0 we dk if we need to update index 0 or index 1...
//
// 2.75 = 2 3/4 , 1/4 less than the m = 3 method.. does this mean we can
// eliminate 1 gues sin the remaining 1/4 of the string?
//
//
void solve() {
  int n;
  cin >> n;

  string s = "";
  char chars[] = {'P', 'I', 'Z', 'A'};

  mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

  for (int i = 0; i < n; ++i) {
    shuffle(chars, chars + 4, rng);

    if (i == n - 1) {
      for (int j = 0; j < 4; ++j) {
        cout << s + chars[j] << endl;
        int res;
        cin >> res;
        if (res == 2) {
          return;
        }
      }
    } else {
      bool found = false;
      for (int j = 0; j < 3; ++j) {
        cout << s + chars[j] << endl;
        int res;
        cin >> res;
        if (res == 1) {
          s += chars[j];
          found = true;
          break;
        }
      }
      if (!found) {
        s += chars[3];
      }
    }
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
