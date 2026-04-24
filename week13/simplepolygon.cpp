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
  long long x, y;
  int id;
};

long long cross_product(Point a, Point b, Point c) {
  return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

long long dist_sq(Point a, Point b) {
  return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

void solve() {
  int n;
  cin >> n;
  vector<Point> pts(n);

  int min_idx = 0;
  for (int i = 0; i < n; i++) {
    cin >> pts[i].x >> pts[i].y;
    pts[i].id = i;
    if (pts[i].y < pts[min_idx].y ||
        (pts[i].y == pts[min_idx].y && pts[i].x < pts[min_idx].x)) {
      min_idx = i;
    }
  }

  swap(pts[0], pts[min_idx]);
  Point p0 = pts[0];

  sort(pts.begin() + 1, pts.end(), [&p0](const Point &a, const Point &b) {
    long long cp = cross_product(p0, a, b);
    if (cp != 0) {
      return cp > 0;
    }
    return dist_sq(p0, a) < dist_sq(p0, b);
  });

  int i = n - 2;
  while (i >= 1 && cross_product(p0, pts[n - 1], pts[i]) == 0) {
    i--;
  }
  reverse(pts.begin() + i + 1, pts.end());

  for (int j = 0; j < n; j++) {
    cout << pts[j].id << (j == n - 1 ? "" : " ");
  }
  cout << "\n";
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;

  while (t--) {
    solve();
  }

  return 0;
}
