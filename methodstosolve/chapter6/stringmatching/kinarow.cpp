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

int dr[] = {0, 1, 1, -1};
int dc[] = {1, 0, 1, 1};

void solve() {
  int games;
  cin >> games;

  int hansel_wins = 0;
  int gretel_wins = 0;

  while (games--) {
    int w, h, k;
    cin >> w >> h >> k;

    vector<string> board(h);

    for (int i = 0; i < h; ++i) {
      cin >> board[i];
    }

    bool hansel_won = false;
    bool gretel_won = false;

    for (int r = 0; r < h; ++r) {
      for (int c = 0; c < w; ++c) {
        if (board[r][c] == '.')
          continue;

        char player = board[r][c];

        for (int d = 0; d < 4; ++d) {
          int end_r = r + (k - 1) * dr[d];
          int end_c = c + (k - 1) * dc[d];

          if (end_r >= 0 && end_r < h && end_c >= 0 && end_c < w) {
            bool valid = true;

            for (int step = 1; step < k; ++step) {
              if (board[r + step * dr[d]][c + step * dc[d]] != player) {
                valid = false;
                break;
              }
            }

            if (valid) {
              if (player == 'x')
                hansel_won = true;
              if (player == 'o')
                gretel_won = true;
              break;
            }
          }
        }
      }
    }

    if (hansel_won)
      hansel_wins++;
    else if (gretel_won)
      gretel_wins++;
  }
  cout << hansel_wins << ":" << gretel_wins << "\n";
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
