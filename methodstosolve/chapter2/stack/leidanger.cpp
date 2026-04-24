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
  string s;
  cin >> s;
  stack<char> stk;
  int cnt[256] = {};
  for (char c : s) {
    if (c == '.') {
      continue;
    }
    if (islower(c)) {
      stk.push(c);
      cnt[c]++;
    } else {
      char target = tolower(c);
      while (!stk.empty() && stk.top() != target) {
        cnt[stk.top()]--;
        stk.pop();
      }
      if (stk.empty()) {
        cout << "Neibb\n";
        return;
      }
      stk.pop();
      cnt[target]--;
    }
  }

  for (char c : {'p', 'g', 'o'})
    cout << cnt[c] << "\n";
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
