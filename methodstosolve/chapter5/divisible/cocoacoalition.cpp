#include <cmath>
#include <iostream>

using namespace std;

// Helper function to check if a target area can form a valid corner piece
bool is_two_cuts(long long target, long long N, long long M) {
  long long limit = sqrt(target);

  // Check all possible factors of the target area
  for (long long a = 1; a <= limit; ++a) {
    if (target % a == 0) {
      long long b = target / a;

      // Check if this a x b block physically fits inside the N x M grid
      // We check both orientations (a x b) and (b x a)
      if ((a <= N && b <= M) || (b <= N && a <= M)) {
        return true;
      }
    }
  }
  return false;
}

void solve() {
  long long N, M, S;

  // Read input
  if (cin >> N >> M >> S) {
    long long A = N * M;

    // Case 1: 1 Cut
    if (S % N == 0 || S % M == 0) {
      cout << 1 << "\n";
      return;
    }

    // Case 2: 2 Cuts (Either Alice gets a corner, or Bob gets a corner)
    if (is_two_cuts(S, N, M) || is_two_cuts(A - S, N, M)) {
      cout << 2 << "\n";
      return;
    }

    // Case 3: 3 Cuts (Always possible if 1 and 2 fail)
    cout << 3 << "\n";
  }
}

int main() {
  // Fast I/O
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  // Note: The problem description says "The input consists of a single line",
  // so there are no test cases (T). We just call solve() once.
  solve();

  return 0;
}
