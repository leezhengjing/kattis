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

void solve(int tc) {
  int n, p, q;
  cin >> n >> p >> q;

  vi prince(p + 1);

  unordered_map<int, int> idx_to_rank;
  for (int i = 0; i <= p; ++i) {
    cin >> prince[i];
    idx_to_rank[prince[i]] = i + 1;
  }

  vi princess;

  for (int i = 0; i <= q; ++i) {
    int val;
    cin >> val;
    if (idx_to_rank.count(val)) {
      princess.push_back(idx_to_rank[val]);
    }
  }

  vi tails;

  for (int rank : princess) {
    auto it = lower_bound(tails.begin(), tails.end(), rank);

    if (it == tails.end()) {
      tails.push_back(rank);
    } else {
      *it = rank;
    }
  }

  cout << "Case " << tc << ": " << tails.size() << "\n";
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;

  for (int i = 1; i <= t; ++i) {
    solve(i);
  }

  return 0;
}
