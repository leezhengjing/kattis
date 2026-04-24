#include <bits/stdc++.h>
// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/tree_policy.hpp>
using namespace std;
// using namespace __gnu_pbds;

typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef tuple<int, ll, ll> edge;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<vi> vvi;

#define LSOne(S) ((S) & -(S))
// int two_pow_p1 = LSOne(mask);
// int p1 = __builtin_ctz(two_pow_p1);
#define REP(i, s, t) for (int i = (s); i < (t); ++i)

const ll INF = 1e18;
template <class T> T read() {
  T v;
  std::cin >> v;
  return v;
}

void fast_io() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
}

void solve() {
  int n, m, k;
  cin >> n >> m >> k;

  priority_queue<pair<string, int>, vector<pair<string, int>>,
                 greater<pair<string, int>>>
      pq;
  vector<pair<ll, pair<string, int>>> to_receive;
  pq.push({"Jane Eyre", k});

  for (int i = 0; i < n; ++i) {
    string title;
    int pages;

    // cin >> ws;
    char quote;
    cin >> quote;

    getline(cin, title, '"');
    cin >> pages;
    // cout << title << "\n";
    pq.push({title, pages});
  }

  for (int i = 0; i < m; ++i) {
    ll time;
    string title;
    int pages;

    cin >> time;
    char quote;
    cin >> quote;
    getline(cin, title, '"');
    cin >> pages;
    to_receive.push_back({time, {title, pages}});
  }

  sort(to_receive.begin(), to_receive.end());

  // for (auto const &item : to_receive) {
  //   cout << item.first << item.second.first << item.second.second << "\n";
  // }

  int idx = 0;
  ll curr_time = 0;
  while (!pq.empty() && pq.top().first != "Jane Eyre") {
    auto curr = pq.top();
    pq.pop();
    curr_time += curr.second;
    while (idx < m && to_receive[idx].first <= curr_time) {
      pq.push(to_receive[idx].second);
      idx++;
    }
  }
  cout << curr_time + pq.top().second << "\n";
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
