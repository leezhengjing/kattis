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
  int N;
  cin >> N;

  vector<string> encrypted(N);
  for (int i = 0; i < N; ++i) {
    cin >> encrypted[i];
  }

  string D, X;
  cin >> D >> X;

  vector<vector<char>> valid_mappings;

  for (const string &E : encrypted) {
    if (E.length() != D.length())
      continue;

    vector<char> e_to_d(26, '?');
    vector<char> d_to_e(26, '?');
    bool possible = true;
    int count = 0;

    for (int i = 0; i < E.length(); ++i) {
      int u = E[i] - 'a';
      int v = D[i] - 'a';

      if (e_to_d[u] != '?' && e_to_d[u] != D[i]) {
        possible = false;
        break;
      }
      if (d_to_e[v] != '?' && d_to_e[v] != E[i]) {
        possible = false;
        break;
      }

      if (e_to_d[u] == '?') {
        e_to_d[u] = D[i];
        d_to_e[v] = E[i];
        count++;
      }
    }

    if (possible) {
      if (count == 25) {
        char unmapped_e = '?';
        char unmapped_d = '?';
        for (int i = 0; i < 26; ++i) {
          if (e_to_d[i] == '?')
            unmapped_e = i + 'a';
          if (d_to_e[i] == '?')
            unmapped_d = i + 'a';
        }
        e_to_d[unmapped_e - 'a'] = unmapped_d;
      }
      valid_mappings.push_back(e_to_d);
    }
  }

  if (valid_mappings.empty()) {
    cout << "IMPOSSIBLE\n";
    return;
  }

  string ans = "";
  for (char c : X) {
    int idx = c - 'a';
    char target = valid_mappings[0][idx];

    if (target != '?') {
      for (int i = 1; i < valid_mappings.size(); ++i) {
        if (valid_mappings[i][idx] != target) {
          target = '?';
          break;
        }
      }
    }

    ans += target;
  }

  cout << ans << "\n";
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
