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

void fast_io() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
}

template <typename T> vector<T> get_words() {
  string line;
  getline(std::cin, line);
  istringstream ss{line};
  ss >> boolalpha;
  vector<T> v;
  copy(istream_iterator<T>{ss}, istream_iterator<T>{}, back_inserter(v));
  return v;
}

template <typename T> void put_words(const vector<T> &v) {
  if (!v.empty()) {
    copy(v.begin(), prev(v.end()), ostream_iterator<T>{cout, " "});
    cout << v.back();
  }
  cout << '\n';
}

unordered_map<int, ll> ans = {

    {24, 1389537}, {23, 755476}, {22, 410744}, {21, 223317}, {20, 121415},
    {19, 66012},   {18, 35890},  {17, 19513},  {16, 10609},  {15, 5768},
    {14, 3136},    {1, 1},       {2, 2},       {3, 4},       {4, 7},
    {5, 13},       {6, 24},      {7, 44},      {8, 81},      {9, 149},
    {10, 274},     {11, 504},    {12, 927},    {13, 1705},
};

ll dfs(int start_index) {
  if (ans.count(start_index)) {
    return ans[start_index];
  }
  if (start_index < 0) {
    return 0;
  }

  if (start_index == 0) {
    return 1;
  }

  ll ans = 0;

  for (int i = 1; i <= 3; ++i) {
    ans += dfs(start_index - i);
  }

  return ans;
}

void precompute() {
  for (int i = 1; i <= 24; ++i) {
    ans[i] = dfs(i);
  }
}

void solve() {
  // cin.ignore(numeric_limits<streamsize>::max(), '\n');
  // cout << "unordered_map<int, ll> ans = {\n" << "\n";
  // for (auto const &[key, value] : ans) {
  //   cout << "{" << key << "," << value << "},\n";
  // }
  // cout << "}\n";
  int n;
  cin >> n;
  cout << ans[n] << "\n";
}

int main() {
  fast_io();

  int t = 1;
  // precompute();
  // cin >> t;

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
