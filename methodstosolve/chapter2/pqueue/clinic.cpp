#include <bits/stdc++.h>
// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/tree_policy.hpp>
using namespace std;
// using namespace __gnu_pbds;

typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef tuple<int, ll, ll> edge; // For MaxFlow
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

struct CustomCmp {
  bool operator()(const pair<ll, string> &a, const pair<ll, string> &b) const {
    if (a.first == b.first) {
      return a.second > b.second;
    }
    return a.first < b.first;
  }
};

int N, K;
void solve() {
  priority_queue<pair<ll, string>, vector<pair<ll, string>>, CustomCmp> pq;
  unordered_set<string> left;
  cin >> N >> K;
  while (N--) {
    int type;
    ll T;
    cin >> type >> T;
    if (type == 1) {
      string M;
      ll S;
      cin >> M >> S;
      pq.push({S - K * T, M});
    } else if (type == 2) {
      while (!pq.empty() && left.find(pq.top().second) != left.end()) {
        pq.pop();
      }
      if (pq.empty())
        cout << "doctor takes a break\n";
      else {
        auto candidate = pq.top();
        cout << candidate.second << "\n";
        pq.pop();
      }
    } else if (type == 3) {
      string M;
      cin >> M;
      left.emplace(M);
    }
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t >> K;

  while (t--) {
    solve();
  }

  return 0;
}
