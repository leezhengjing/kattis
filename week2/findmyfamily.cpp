
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> ii;
typedef vector<ii> vii;

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
void solve() {
  int k;
  cin >> k;
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  int res = 0;
  vi indices;
  for (int l = 0; l < k; ++l) {
    int n;
    cin >> n;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    vi arr = get_words<int>();
    set<int> prefix_set;
    prefix_set.insert(arr[0]);
    vi suffix_max(n + 1, 0);
    for (int i = n - 1; i >= 0; --i) {
      suffix_max[i] = max(arr[i], suffix_max[i + 1]);
    }

    for (int i = 1; i < n; ++i) {
      if (prefix_set.upper_bound(arr[i]) != prefix_set.end() &&
          *prefix_set.upper_bound(arr[i]) < suffix_max[i + 1]) {
        ++res;
        indices.push_back(l + 1);
        break;
      }
      prefix_set.insert(arr[i]);
    }
  }
  cout << res << endl;
  for (int i = 0; i < indices.size(); ++i) {
    cout << indices[i] << endl;
  }
}

int main() {
  fast_io();

  int t = 1;

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
