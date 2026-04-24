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

bool is_palindrome(const string &s, int left, int right) {
  while (left < right) {
    if (s[left] != s[right])
      return false;
    left++;
    right--;
  }
  return true;
}

void solve() {
  string s;
  if (!(cin >> s))
    return;

  int n = s.length();
  int left = 0, right = n - 1;

  // Move pointers inward until a mismatch is found
  while (left < right && s[left] == s[right]) {
    left++;
    right--;
  }

  // CASE 1: The string is already a palindrome
  if (left >= right) {
    int mid1 = (n - 1) / 2;
    int mid2 = n / 2;
    char target = s[mid1];

    int ans = 0;

    // Count identical characters leftwards from center
    int l_ptr = mid1;
    while (l_ptr >= 0 && s[l_ptr] == target) {
      ans++;
      l_ptr--;
    }

    // Count identical characters rightwards from center
    int r_ptr = mid2;
    while (r_ptr < n && s[r_ptr] == target) {
      ans++;
      r_ptr++;
    }

    // If the string length is odd, mid1 and mid2 are the exact same index,
    // meaning we counted the center character twice. Subtract 1.
    if (n % 2 != 0)
      ans--;

    cout << ans << "\n";
    return;
  }

  // CASE 2: Mismatch found at 'left' and 'right'
  int ans = 0;

  // Option A: Try ignoring the left character
  if (is_palindrome(s, left + 1, right)) {
    char target = s[left];
    int ptr = left;
    // Count how many consecutive identical characters we can safely remove
    while (ptr >= 0 && s[ptr] == target) {
      ans++;
      ptr--;
    }
  }

  // Option B: Try ignoring the right character
  if (is_palindrome(s, left, right - 1)) {
    char target = s[right];
    int ptr = right;
    // Count how many consecutive identical characters we can safely remove
    while (ptr < n && s[ptr] == target) {
      ans++;
      ptr++;
    }
  }

  cout << ans << "\n";
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
