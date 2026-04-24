#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> ii;
typedef vector<ii> vii;

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

typedef tree<string, null_type, less<string>, rb_tree_tag,
             tree_order_statistics_node_update>
    ost;

int query_tree(ost &tree, const string &start, const string &end) {
  return tree.order_of_key(end) - tree.order_of_key(start);
}

void solve() {
  // cin.ignore(numeric_limits<streamsize>::max(), '\n');
  ost male_tree;
  ost female_tree;
  int command;
  unordered_map<string, int> gender_map;
  while (cin >> command && command != 0) {
    if (command == 1) {
      string name;
      int gender;
      cin >> name >> gender;

      gender_map[name] = gender;

      if (gender == 1) {
        male_tree.insert(name);
      } else {
        female_tree.insert(name);
      }

    } else if (command == 2) {
      string name;
      cin >> name;
      int gender;
      gender = gender_map[name];

      gender_map.erase(name);
      if (gender == 1) {
        male_tree.erase(name);
      } else {
        female_tree.erase(name);
      }

    } else if (command == 3) {
      string start, end;
      int gender;
      cin >> start >> end >> gender;
      int res = 0;
      if (gender == 0) {
        res += query_tree(male_tree, start, end);
        res += query_tree(female_tree, start, end);
      } else if (gender == 1) {
        res += query_tree(male_tree, start, end);
      } else if (gender == 2) {
        res += query_tree(female_tree, start, end);
      }
      cout << res << "\n";
    }
  };
}

int main() {
  fast_io();

  int t = 1;
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
