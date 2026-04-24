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

const string morse_alpha[26] = {
    ".-",   "-...", "-.-.", "-..",  ".",   "..-.", "--.",  "....", "..",
    ".---", "-.-",  ".-..", "--",   "-.",  "---",  ".--.", "--.-", ".-.",
    "...",  "-",    "..-",  "...-", ".--", "-..-", "-.--", "--.."};

const string morse_digit[10] = {"-----", ".----", "..---", "...--", "....-",
                                ".....", "-....", "--...", "---..", "----."};

bool is_palindrome(const string &s) {
  int l = 0, r = s.length() - 1;
  while (l < r) {
    if (s[l++] != s[r--])
      return false;
  }
  return true;
}

void fast_io() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
}

void solve() {
  string s;
  getline(cin, s);

  string morse_str = "";

  for (char c : s) {
    if (isalnum(c)) {
      c = toupper(c);

      if (isalpha(c)) {
        morse_str += morse_alpha[c - 'A'];
      } else if (isdigit(c)) {
        morse_str += morse_digit[c - '0'];
      }
    }
  }

  if (morse_str.empty()) {
    cout << 0 << "\n";
    return;
  }

  if (is_palindrome(morse_str)) {
    cout << 1 << "\n";
  } else {
    cout << 0 << "\n";
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
