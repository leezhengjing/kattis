#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef vector<pair<int, int>> vii;
typedef vector<ll> vll;
typedef pair<int, int> ii;

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

template <typename T> deque<T> get_words_deque() {
  string line;
  getline(std::cin, line);
  istringstream ss{line};
  ss >> boolalpha;
  deque<T> d;
  copy(istream_iterator<T>{ss}, istream_iterator<T>{}, back_inserter(d));
  return d;
}

template <typename T> void put_words(const vector<T> &v) {
  if (!v.empty()) {
    copy(v.begin(), prev(v.end()), ostream_iterator<T>{cout, " "});
    cout << v.back();
  }
  cout << '\n';
}

struct custom_cmp {
  bool operator()(const ii &a, const ii &b) const {
    if (a.first != b.first) {
      return a.first < b.first;
    }
    return a.second < b.second;
  }
};

void solve() {
  int C, P;
  cin >> C >> P;
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  vi eliminated(C + 1, 0);
  vector<deque<int>> parties;
  vi parties_votes(P);
  vi curr_candidate_votes(C + 1, 0);
  int vote_sum = 0;

  set<ii, custom_cmp> s;
  for (int i = 1; i <= C; ++i) {
    s.insert({0, i});
  }

  for (int i = 0; i < P; ++i) {
    deque<int> party = get_words_deque<int>();
    int num_votes = party.front();
    parties_votes[i] = num_votes;
    vote_sum += num_votes;
    party.pop_front();
    parties.push_back(std::move(party));

    if (!parties[i].empty()) {
      int first_choice = parties[i].front();

      s.erase({curr_candidate_votes[first_choice], first_choice});
      curr_candidate_votes[first_choice] += num_votes;
      s.insert({curr_candidate_votes[first_choice], first_choice});
    }
  }

  for (int i = 0; i < C; ++i) {
    ii smallest = *s.begin();
    ii largest = *s.rbegin();

    if (s.size() == 1 || largest.first > vote_sum / 2) {
      cout << largest.second << endl;
      return;
    }

    s.erase(s.begin());
    eliminated[smallest.second] = 1;

    for (int k = 0; k < P; ++k) {
      if (!parties[k].empty() && parties[k].front() == smallest.second) {
        while (!parties[k].empty() && eliminated[parties[k][0]]) {
          parties[k].pop_front();
        }
        int next_choice = parties[k].front();
        s.erase({curr_candidate_votes[next_choice], next_choice});
        curr_candidate_votes[next_choice] += parties_votes[k];
        s.insert({curr_candidate_votes[next_choice], next_choice});
      }
    }
  }
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
