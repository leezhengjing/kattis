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
  // cin.ignore(numeric_limits<streamsize>::max(), '\n');
  int n, m;
  cin >> n >> m;

  vi arr;
  for (int i = 1; i <= n; ++i) {
    arr.push_back(i);
  }

  for (int i = 0; i < m; ++i) {
    string winner, loser;
    cin >> winner >> loser;
    int winning_team = stoi(winner.substr(1));
    int losing_team = stoi(loser.substr(1));

    auto iterator_win = find(arr.begin(), arr.end(), winning_team);
    auto iterator_lose = find(arr.begin(), arr.end(), losing_team);

    int win_index = distance(arr.begin(), iterator_win);
    int lose_index = distance(arr.begin(), iterator_lose);

    if (lose_index < win_index) {
      rotate(iterator_lose, iterator_lose + 1, iterator_win + 1);
    }
  }

  for (int i = 0; i < n; ++i) {
    cout << "T" << arr[i] << (i == n - 1 ? "" : " ");
  }
  // unordered_map<int, int> val_to_index;
  // unordered_map<int, int> index_to_val;
  // val_to_index.reserve(n);
  // for (int i = 1; i <= n; ++i) {
  //   val_to_index[i] = i;
  //   index_to_val[i] = i;
  // }
  // string winner, loser;
  // int winner_id, loser_id;
  // for (int i = 0; i < m; ++i) {
  //   cin >> winner >> loser;
  //   winner_id = val_to_index[stoi(winner.substr(1))];
  //   loser_id = val_to_index[stoi(loser.substr(1))];
  //   if (winner_id > loser_id) {
  //     for (int j = loser_id + 1; j <= winner_id; ++j) {
  //       index_to_val[j - 1] = index_to_val[j];
  //       val_to_index[index_to_val[j]]--;
  //     }
  //     index_to_val[winner_id] = stoi(loser.substr(1));
  //     val_to_index[stoi(loser.substr(1))] = winner_id;
  //   }
  // }
  //
  // for (int i = 1; i < n; ++i) {
  //   cout << "T" << index_to_val[i] << " ";
  // }
  // cout << "T" << index_to_val[n] << endl;
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
