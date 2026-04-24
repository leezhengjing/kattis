#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <thread>
using namespace std;
using namespace __gnu_pbds;

typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> ii;
typedef vector<pair<int, int>> vii;

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

class background_task {
public:
  void operator()() const { cout << "hi" << endl; }
};

struct custom_cmp {
  bool operator()(pair<ii, int> a, pair<ii, int> b) const {
    if (a.first.first != b.first.first) {
      return a.first.first > b.first.first;
    }
    if (a.first.second != b.first.second)
      return a.first.second < b.first.second;
    return a.second < b.second;
  }
};
using indexed_set = tree<pair<ii, int>, null_type, custom_cmp, rb_tree_tag,
                         tree_order_statistics_node_update>;
void solve() {

  int n, m;
  cin >> n >> m;
  indexed_set s;
  vector<ii> team_scores(n + 1, {0, 0});
  for (int i = 1; i < n + 1; ++i) {
    s.insert({{team_scores[i].first, team_scores[i].second}, i});
  }
  for (int i = 0; i < m; ++i) {
    int id, penalty;
    cin >> id >> penalty;

    ii prev = team_scores[id];

    int new_score = prev.first + 1;
    int new_penalty = prev.second + penalty;
    s.erase({{prev.first, prev.second}, id});
    team_scores[id] = {new_score, new_penalty};
    s.insert({{new_score, new_penalty}, id});

    int rank = s.order_of_key({team_scores[1], 1});
    cout << rank + 1 << endl;
  }
}

int main() {
  fast_io();

  int t = 1;

  background_task f;
  std::thread my_thread(f);

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
