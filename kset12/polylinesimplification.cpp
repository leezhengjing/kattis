#include <bits/stdc++.h>

// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/tree_policy.hpp>
using namespace std;
// using namespace __gnu_pbds;

typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef tuple<int, ll, ll> edge;
// typedef tuple<int, ll, ll, ll> edge;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<vi> vvi;

#define LSOne(S) ((S) & -(S))
// int two_pow_p1 = LSOne(mask);
// int p1 = __builtin_ctz(two_pow_p1);
#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define sz(x) (int)(x).size()

const ll INF = 1e18;
const int MOD = 1e9 + 7;

void fast_io() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
}

struct Point {
  ll x, y;
};

// Calculates 2 * Area of the triangle to keep everything in fast, exact
// integers
ll getArea(const Point &a, const Point &b, const Point &c) {
  return abs((b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y));
}

// State for the Priority Queue
struct State {
  ll area;
  int idx;

  // Custom comparator for min-heap
  bool operator>(const State &other) const {
    if (area != other.area)
      return area > other.area;
    return idx > other.idx; // Tie-breaker: lowest index wins
  }
};

void solve() {
  int n, m;
  if (!(cin >> n >> m))
    return;

  // A polyline with n segments has n + 1 points
  vector<Point> pts(n + 1);
  rep(i, 0, n + 1) { cin >> pts[i].x >> pts[i].y; }

  // Doubly linked list representation
  vi prev_idx(n + 1);
  vi next_idx(n + 1);
  vll current_area(n + 1, -1);
  vector<bool> active(n + 1, true);

  // Min Priority Queue
  priority_queue<State, vector<State>, greater<State>> pq;

  // Initialize links
  rep(i, 0, n + 1) {
    prev_idx[i] = i - 1;
    next_idx[i] = i + 1;
  }

  // Initialize areas
  rep(i, 1, n) {
    current_area[i] = getArea(pts[prev_idx[i]], pts[i], pts[next_idx[i]]);
    pq.push({current_area[i], i});
  }

  int to_remove = n - m;
  while (to_remove > 0) {
    State curr = pq.top();
    pq.pop();

    int i = curr.idx;

    // Lazy Deletion: Ignore if already removed or if the area is outdated
    if (!active[i] || current_area[i] != curr.area)
      continue;

    // Remove the point
    active[i] = false;
    cout << i << "\n";
    to_remove--;

    // Find current neighbors
    int l = prev_idx[i];
    int r = next_idx[i];

    // Update the doubly linked list
    if (l >= 0)
      next_idx[l] = r;
    if (r <= n)
      prev_idx[r] = l;

    // Update the area for the left neighbor (if it's not the first point)
    if (l > 0) {
      current_area[l] = getArea(pts[prev_idx[l]], pts[l], pts[next_idx[l]]);
      pq.push({current_area[l], l});
    }

    // Update the area for the right neighbor (if it's not the last point)
    if (r < n) {
      current_area[r] = getArea(pts[prev_idx[r]], pts[r], pts[next_idx[r]]);
      pq.push({current_area[r], r});
    }
  }
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
