#include <bits/stdc++.h>
// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/tree_policy.hpp>
using namespace std;
// using namespace __gnu_pbds;

typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<vi> vvi;

#define LSOne(S) ((S) & -(S))
// int two_pow_p1 = LSOne(mask);
// int p1 = __builtin_ctz(two_pow_p1);
#define REP(i, s, t) for (int i = (s); i < (t); ++i)

template <class T> T read() {
  T v;
  std::cin >> v;
  return v;
}

void fast_io() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
}

bool solved = false;
string s1, s2, s3;

bool is_valid(unordered_map<char, int> &char_to_digit) {
  int i = s1.length() - 1, j = s2.length() - 1, k = s3.length() - 1;

  int carry = 0;

  while (i >= 0 || j >= 0 || k >= 0 || carry) {
    int d1 = (i >= 0) ? char_to_digit[s1[i]] : 0;
    int d2 = (j >= 0) ? char_to_digit[s2[j]] : 0;
    int sum = d1 + d2 + carry;

    int expected = (k >= 0) ? char_to_digit[s3[k]] : 0;

    if (k < 0)
      return false;

    if (sum % 10 != expected)
      return false;
    carry = sum / 10;
    i--;
    j--;
    k--;
  }

  return (i < 0 && j < 0 && k < 0 && carry == 0);
}

void dfs(int start_index, const vector<char> &arr,
         const unordered_set<char> leading_chars, vector<bool> &visited,
         unordered_map<char, int> &char_to_digit) {
  if (solved)
    return;

  if (start_index == arr.size()) {
    if (is_valid(char_to_digit)) {
      solved = true;

      for (char c : s1)
        cout << char_to_digit[c];
      cout << "+";
      for (char c : s2)
        cout << char_to_digit[c];
      cout << "=";
      for (char c : s3)
        cout << char_to_digit[c];
      cout << "\n";
    }

    return;
  }

  char curr = arr[start_index];

  for (int d = 0; d <= 9; ++d) {
    if (!visited[d]) {
      if (d == 0 && leading_chars.count(curr))
        continue;

      visited[d] = true;
      char_to_digit[curr] = d;

      dfs(start_index + 1, arr, leading_chars, visited, char_to_digit);
      if (solved)
        return;

      visited[d] = false;
    }
  }
}

void solve() {
  // cin.ignore(numeric_limits<streamsize>::max(), '\n');
  string line;
  cin >> line;

  vector<char> arr;
  unordered_map<char, int> char_to_digit;
  unordered_set<char> leading_chars;
  unordered_set<char> distinct;

  int plus_idx = line.find('+');
  int eq_idx = line.find('=');

  s1 = line.substr(0, plus_idx);
  s2 = line.substr(plus_idx + 1, eq_idx - (plus_idx + 1));
  s3 = line.substr(eq_idx + 1);

  vector<bool> visited(10, false);

  for (char c : s1)
    distinct.insert(c);
  for (char c : s2)
    distinct.insert(c);
  for (char c : s3)
    distinct.insert(c);

  for (char c : distinct)
    arr.push_back(c);

  leading_chars.insert(s1[0]);
  leading_chars.insert(s2[0]);
  leading_chars.insert(s3[0]);

  sort(arr.begin(), arr.end());

  if (s3.length() < max(s1.length(), s2.length()) ||
      s3.length() > max(s1.length(), s2.length()) + 1) {
    cout << "impossible" << "\n";
    return;
  }

  dfs(0, arr, leading_chars, visited, char_to_digit);

  if (!solved) {
    cout << "impossible" << "\n";
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  //

  while (t--) {
    // code here
    solve();
  }

  // reading input
  // read int: int n; cin >> n;
  // read line: string s; getline(cin, s);
  // read list/arr: vi arr(n); for(int i=0; i<n; ++i) cin >> arr[i];
  // eof reading: int n; while(cin >> n) { ... }

  return 0;
}
