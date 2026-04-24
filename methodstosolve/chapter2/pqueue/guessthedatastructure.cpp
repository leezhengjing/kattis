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

int N;
void solve() {
  stack<int> stk;
  queue<int> q;
  priority_queue<int> pq;
  bool is_stk = true, is_q = true, is_pq = true;
  for (int i = 0; i < N; ++i) {
    int a, b;
    cin >> a >> b;
    if (a == 1) {
      if (is_stk)
        stk.push(b);
      if (is_q)
        q.push(b);
      if (is_pq)
        pq.push(b);
    } else if (a == 2) {

      if (is_stk) {
        if (stk.empty() || stk.top() != b)
          is_stk = false;
        else
          stk.pop();
      }
      if (is_q) {
        if (q.empty() || q.front() != b)
          is_q = false;
        else
          q.pop();
      }
      if (is_pq) {
        if (pq.empty() || pq.top() != b)
          is_pq = false;
        else
          pq.pop();
      }
      // if (stk.empty()) {
      //   cout << "impossible\n";
      //   return;
      // }
      // int stk_top = stk.top();
      // int q_top = q.front();
      // int pq_top = pq.top();
      // stk.pop();
      // q.pop();
      // pq.pop();
      // if (b != stk_top) {
      //   is_stk = false;
      // }
      // if (b != q_top) {
      //   is_q = false;
      // }
      // if (b != pq_top) {
      //   is_pq = false;
      // }
    }
  }
  int count = (int)is_stk + (int)is_q + (int)is_pq;
  if (count == 0) {
    cout << "impossible\n";
  } else if (count > 1) {
    cout << "not sure\n";
  } else if (is_stk) {
    cout << "stack\n";
  } else if (is_q) {
    cout << "queue\n";
  } else if (is_pq) {
    cout << "priority queue\n";
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;

  while (cin >> N) {
    solve();
  }

  return 0;
}
