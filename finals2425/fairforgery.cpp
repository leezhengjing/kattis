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
const int MOD = 1e9 + 7;

void fast_io() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
}

void solve() {
  int n, m, k;
  cin >> n >> m >> k;
  // ranks[x] will store all the 1-based ranks candidate x received across all M
  // votes
  vvi ranks(n + 1);
  for (int i = 1; i <= n; ++i) {
    ranks[i].reserve(m);
  }

  // Read the M votes
  for (int i = 0; i < m; ++i) {
    for (int r = 1; r <= n; ++r) {
      int x;
      cin >> x;
      ranks[x].push_back(r);
    }
  }

  // T is ceil(M / K)
  int T = (m + k - 1) / k;

  // Store pairs of (E_x, candidate_id)
  vii E_vals;
  E_vals.reserve(n);

  for (int x = 1; x <= n; ++x) {
    // Find the T-th smallest rank for candidate x (0-indexed, so we look at T -
    // 1) nth_element is O(M) and avoids doing a full O(M log M) sort
    nth_element(ranks[x].begin(), ranks[x].begin() + T - 1, ranks[x].end());

    int Ex = ranks[x][T - 1];
    E_vals.push_back({Ex, x});
  }

  // Sort candidates based on their required rank E_x in ascending order
  sort(E_vals.begin(), E_vals.end());

  // Extract the sorted candidate IDs into a clean array C
  vi C(n);
  for (int j = 0; j < n; ++j) {
    C[j] = E_vals[j].second;
  }

  // Generate and print the K forged votes
  for (int v = 0; v < k; ++v) {
    bool first = true;

    // Step 1: Place the candidates critically assigned to Vote 'v'
    for (int j = 0; j < n; ++j) {
      if (j % k == v) {
        if (!first)
          cout << " ";
        cout << C[j];
        first = false;
      }
    }

    // Step 2: Fill the remaining slots with all other candidates to complete
    // the permutation
    for (int j = 0; j < n; ++j) {
      if (j % k != v) {
        if (!first)
          cout << " ";
        cout << C[j];
        first = false;
      }
    }
    cout << "\n";
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
