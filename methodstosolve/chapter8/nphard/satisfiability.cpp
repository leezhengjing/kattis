#include <bits/stdc++.h>
// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/tree_policy.hpp>
using namespace std;
// using namespace __gnu_pbds;

typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
// typedef tuple<int, ll, ll> edge;
typedef tuple<int, ll, ll, ll> edge;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<vi> vvi;

#define LSOne(S) ((S) & -(S))
// int two_pow_p1 = LSOne(mask);
// int p1 = __builtin_ctz(two_pow_p1);
#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define sz(x) (int)(x).size()

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
  int n, m;
  cin >> n >> m;

  vi pos_masks(m, 0);
  vi neg_masks(m, 0);

  string line;
  getline(cin, line);

  for (int i = 0; i < m; ++i) {
    getline(cin, line);
    stringstream ss(line);
    string token;

    while (ss >> token) {
      if (token == "v")
        continue;

      if (token[0] == '~') {
        int idx = stoi(token.substr(2)) - 1;
        neg_masks[i] |= (1 << idx);
      } else {
        int idx = stoi(token.substr(1)) - 1;
        pos_masks[i] |= (1 << idx);
      }
    }
  }

  int total_states = 1 << n;
  bool satisfiable = false;

  for (int state = 0; state < total_states; ++state) {
    bool ok = true;

    for (int i = 0; i < m; ++i) {
      if (!(state & pos_masks[i]) && !(~state & neg_masks[i])) {
        ok = false;
        break;
      }
    }

    if (ok) {
      satisfiable = true;
      break;
    }
  }

  if (satisfiable)
    cout << "satisfiable\n";
  else
    cout << "unsatisfiable\n";
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;

  while (t--) {
    solve();
  }

  return 0;
}
