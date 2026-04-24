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

int N;
vector<int> word_masks;

const int target_mask = (1 << 26) - 1;

void fast_io() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
}

ll solve(int idx, int curr_mask) {
  if (curr_mask == target_mask)
    return 1LL << (N - idx);

  if (idx == N)
    return 0;

  ll count = solve(idx + 1, curr_mask);

  count += solve(idx + 1, curr_mask | word_masks[idx]);

  return count;
}

int main() {
  fast_io();

  cin >> N;
  word_masks.resize(N);

  for (int i = 0; i < N; ++i) {
    string s;
    cin >> s;

    int mask = 0;
    for (char c : s) {
      mask |= (1 << (c - 'a'));
    }

    word_masks[i] = mask;
  }

  cout << solve(0, 0) << "\n";

  return 0;
}
