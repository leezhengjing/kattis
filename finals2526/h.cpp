i/ CP Geometry Templates — exhaustive collection for competitive programming
// Copy this entire file into your snippet library; each section is
// self-contained
//
// ========================== FUNCTION INDEX ==========================
// ctrl+F the function name to jump to its definition
//
// --- FLOATING-POINT TRICKS ---
// EPS / sgn(x)               robust sign with tolerance
// feq / fle / flt            equality / <= / < with tolerance
// safe_sqrt(x)               sqrt with negative-clamp for tiny <0 values
// safe_acos(x)               acos clamped to [-1,1]
// INTEGER COORDS RULE        prefer integer / __int128 cross products
// SCALE RULE                 scale tolerance with magnitude (rel + abs eps)
//
// --- POINT / VECTOR (2D) ---
// Pt                         struct with x,y (templated double or ll)
// Pt + - * /                 vector arithmetic, scalar mul/div
// dot(a,b)                   a.x*b.x + a.y*b.y
// cross(a,b)                 a.x*b.y - a.y*b.x   (signed parallelogram area)
// cross(O,A,B)               cross(A-O, B-O)     (orient test around O)
// norm2(a)                   squared length (exact for ints!)
// abs(a)                     length = sqrt(norm2)
// dist2(a,b) / dist(a,b)
// angle(a)                   atan2(y,x)
// angle(a,b)                 angle between vectors via atan2(cross,dot)
// rotate(p,ang)              rotate by radians around origin
// rotate90(p)                {-y, x}, exact for ints
// perp(p)                    same as rotate90
// unit(p)                    p / |p|
// normal(p)                  unit perpendicular
//
// --- ORIENTATION ---
// orient(a,b,c)              sign of cross(b-a,c-a):  +1 ccw, -1 cw, 0
// collinear collinear(a,b,c) in_angle(a,b,c,p)          is p inside angle <bac
// (assuming b,c on either side)
//
// --- LINES & SEGMENTS ---
// Line{a,b,c}                ax+by+c=0 form;  from_pts(P,Q) builder
// line_from_points(p,q)
// line_eval(L,p)             a*p.x+b*p.y+c, sign tells side
// lines_intersect(L1,L2,&out) false if parallel
// seg_intersect_proper(a,b,c,d)   strict crossing (no shared
// endpoints/colinear) seg_intersect(a,b,c,d)     including touching/overlap
// seg_seg_intersection(a,b,c,d,&out) compute the intersection point/segment
// point_on_segment(p,a,b)    collinear AND within bounding box
// dist_point_line(p,a,b)
// dist_point_segment(p,a,b)
// dist_segment_segment(a,b,c,d)
// project_point_line(p,a,b)  foot of perpendicular
// reflect_point_line(p,a,b)
//
// --- POLYGON BASICS ---
// signed_area(poly)          0.5 * sum of cross(p[i],p[i+1]); sign =
// orientation area(poly)                 abs(signed_area) is_ccw(poly)
// perimeter(poly)
// centroid(poly)             area-weighted centroid (NOT vertex average)
// polygon_contains(poly,p)   0 outside, 1 boundary, 2 inside (winding/ray cast)
// point_in_convex(poly,p)    O(log N) via binary search on fans
// is_convex(poly)            checks all turns same sign
// pick_theorem(area,B)       interior lattice points: I = A - B/2 + 1
// boundary_lattice_pts(poly) sum of gcd(|dx|,|dy|) over edges
//
// --- CONVEX HULL ---
// convex_hull(pts)           Andrew monotone chain, O(N log N), CCW, no
// duplicates
//                            include collinear? -> use < vs <= in cross check
// hull_diameter(hull)        rotating calipers, farthest pair, O(N)
// min_enclosing_rect(hull)   rotating calipers, O(N)
// closest_pair(pts)          divide & conquer, O(N log N)
//
// --- HALF-PLANE INTERSECTION ---
// half_plane_intersect(lines)  O(N log N), returns intersection polygon or
// empty
//
// --- CIRCLES ---
// Circle{c,r}
// circle_line_intersect(C,a,b,&out)
// circle_circle_intersect(C1,C2,&out)
// tangent_from_point(p,C,&out)
// circumcircle(a,b,c)
// incircle(a,b,c)
// min_enclosing_circle(pts)  Welzl, expected O(N)
//
// --- TRIANGLES ---
// triangle_area(a,b,c)       0.5 * |cross(b-a,c-a)|
// triangle_area_signed(a,b,c)
//
// --- ANGULAR SORT ---
// half(p)                    upper(0) / lower(1) half-plane key
// polar_cmp(a,b)             sort by angle around origin without atan2
// sort_by_angle_around(O,pts)
//
// --- POLYGON CUT ---
// polygon_cut(poly, a, b)    cut polygon by line through a,b; keep left side
// (CCW)
//
// --- MINKOWSKI SUM ---
// minkowski_sum(P, Q)        Minkowski sum of two convex polygons (both CCW)
//
// --- SIMPLE POLYGON FROM POINTS ---
// make_simple_polygon(pts)   pivot+angular sort trick (Kattis "simplepolygon")
//
// =============== FLOATING POINT GUIDELINES (READ FIRST) ===============
// 1. PREFER INTEGER ARITHMETIC. If inputs are ints in [-1e4,1e4], cross
//    products fit in ll; in [-1e9,1e9] use __int128. No EPS needed.
// 2. NEVER compare doubles with ==. Use sgn() / feq() with EPS ~ 1e-9.
// 3. Avoid catastrophic cancellation: don't compute (a-b) when a~b unless
//    you scale tolerance. For "is x in [lo,hi]" use x > lo-eps && x < hi+eps.
// 4. acos/asin: clamp arg to [-1,1] (safe_acos). Floating drift can give
// 1+1e-16.
// 5. sqrt of cancellation: clamp negatives to 0 (safe_sqrt).
// 6. atan2(0,0) is undefined behavior region — guard zero vectors.
// 7. For "point on line" tests, use cross() and compare to eps*scale, where
//    scale = max(|a|,|b|,|c|,1). Absolute eps fails on large coords.
// 8. Two segments touching at endpoint vs crossing: decide policy upfront,
//    document it, and write the test accordingly. Most bugs are here.
// 9. When you can, sort/compare by angle using cross-product comparator
//    (polar_cmp), not atan2 — exact for integers, no precision loss.
// 10. Convex hull: feed deduplicated points; tie-break collinear consistently.

// #pragma once
#include <bits/stdc++.h>
using namespace std;

/**
 * FLOATING POINT TRICKS
 */
const double EPS = 1e-12;
const double PI = acos(-1.0);

inline int sgn(double x) { return (x > EPS) - (x < -EPS); }
inline bool feq(double a, double b) { return fabs(a - b) < EPS; }
inline bool fle(double a, double b) { return a < b + EPS; }
inline bool flt(double a, double b) { return a < b - EPS; }
inline double safe_sqrt(double x) { return sqrt(max(0.0, x)); }
inline double safe_acos(double x) { return acos(max(-1.0, min(1.0, x))); }

// Relative+absolute tolerance: use when coordinates can be large.
inline bool feq_rel(double a, double b, double rel = 1e-9,
                    double abs_ = 1e-12) {
  double d = fabs(a - b);
  return d <= abs_ || d <= rel * max(fabs(a), fabs(b));
}

/**
 * POINT / VECTOR 2D
 */
template <class T> struct Pt {
  T x, y;
  Pt(T x = 0, T y = 0) : x(x), y(y) {}
  Pt operator+(const Pt &o) const { return {x + o.x, y + o.y}; }
  Pt operator-(const Pt &o) const { return {x - o.x, y - o.y}; }
  Pt operator*(T k) const { return {x * k, y * k}; }
  Pt operator/(T k) const { return {x / k, y / k}; }
  bool operator==(const Pt &o) const { return x == o.x && y == o.y; }
  bool operator<(const Pt &o) const { return x != o.x ? x < o.x : y < o.y; }
};
using P = Pt<double>;
using Pi = Pt<long long>;

template <class T> T dot(Pt<T> a, Pt<T> b) { return a.x * b.x + a.y * b.y; }
template <class T> T cross(Pt<T> a, Pt<T> b) { return a.x * b.y - a.y * b.x; }
template <class T> T cross(Pt<T> O, Pt<T> A, Pt<T> B) {
  return cross(A - O, B - O);
}
template <class T> T norm2(Pt<T> a) { return dot(a, a); }
template <class T> double absv(Pt<T> a) { return sqrt((double)norm2(a)); }
template <class T> double dist(Pt<T> a, Pt<T> b) { return absv(a - b); }
template <class T> T dist2(Pt<T> a, Pt<T> b) { return norm2(a - b); }

inline double angle(P a) { return atan2(a.y, a.x); }
inline double angle(P a, P b) {
  return atan2(cross(a, b), dot(a, b));
} // signed
inline double angle(Pi a, Pi b) {
  return atan2(cross(a, b), dot(a, b));
} // signed
inline P rotate(P p, double t) {
  return {p.x * cos(t) - p.y * sin(t), p.x * sin(t) + p.y * cos(t)};
}
template <class T> Pt<T> rotate90(Pt<T> p) { return {-p.y, p.x}; }
template <class T> Pt<T> perp(Pt<T> p) { return rotate90(p); }
inline P unit(P p) {
  double L = absv(p);
  return {p.x / L, p.y / L};
}
inline P normal(P p) { return unit(rotate90(p)); }

/**
 * ORIENTATION (use Pi for exact integer test)
 */
template <class T> int orient(Pt<T> a, Pt<T> b, Pt<T> c) {
  T v = cross(b - a, c - a);
  if constexpr (is_floating_point_v<T>)
    return sgn((double)v);
  else
    return (v > 0) - (v < 0);
}
template <class T> bool collinear(Pt<T> a, Pt<T> b, Pt<T> c) {
  return orient(a, b, c) == 0;
}

/**
 * LINES & SEGMENTS
 */
struct Line {
  double a, b, c;
}; // a*x + b*y + c = 0
inline Line line_from_points(P p, P q) {
  return {p.y - q.y, q.x - p.x, cross(p, q)};
}
inline double line_eval(const Line &L, P p) {
  return L.a * p.x + L.b * p.y + L.c;
}

inline bool lines_intersect(const Line &L1, const Line &L2, P &out) {
  double d = L1.a * L2.b - L2.a * L1.b;
  if (feq(d, 0))
    return false;
  out.x = (L2.c * L1.b - L1.c * L2.b) / d;
  out.y = (L1.c * L2.a - L2.c * L1.a) / d;
  return true;
}

// Strict crossing: interiors meet, no shared endpoints, no colinearity.
template <class T>
bool seg_intersect_proper(Pt<T> a, Pt<T> b, Pt<T> c, Pt<T> d) {
  int o1 = orient(a, b, c), o2 = orient(a, b, d);
  int o3 = orient(c, d, a), o4 = orient(c, d, b);
  return o1 != 0 && o2 != 0 && o3 != 0 && o4 != 0 && o1 != o2 && o3 != o4;
}

template <class T> bool point_on_segment(Pt<T> p, Pt<T> a, Pt<T> b) {
  if (orient(a, b, p) != 0)
    return false;
  return min(a.x, b.x) <= p.x && p.x <= max(a.x, b.x) && min(a.y, b.y) <= p.y &&
         p.y <= max(a.y, b.y);
}

// Inclusive: counts endpoint touching and collinear overlap.
template <class T> bool seg_intersect(Pt<T> a, Pt<T> b, Pt<T> c, Pt<T> d) {
  if (seg_intersect_proper(a, b, c, d))
    return true;
  return point_on_segment(c, a, b) || point_on_segment(d, a, b) ||
         point_on_segment(a, c, d) || point_on_segment(b, c, d);
}

inline P project_point_line(P p, P a, P b) {
  P d = b - a;
  return a + d * (dot(p - a, d) / dot(d, d));
}
inline P reflect_point_line(P p, P a, P b) {
  return project_point_line(p, a, b) * 2 - p;
}
inline double dist_point_line(P p, P a, P b) {
  return fabs(cross(b - a, p - a)) / absv(b - a);
}
inline double dist_point_segment(P p, P a, P b) {
  if (a == b)
    return dist(p, a);
  P d = b - a;
  double t = dot(p - a, d) / dot(d, d);
  t = max(0.0, min(1.0, t));
  return dist(p, a + d * t);
}
inline double dist_segment_segment(P a, P b, P c, P d) {
  if (seg_intersect(a, b, c, d))
    return 0;
  return min({dist_point_segment(a, c, d), dist_point_segment(b, c, d),
              dist_point_segment(c, a, b), dist_point_segment(d, a, b)});
}

/**
 * POLYGON BASICS  (poly given as vector<P> or vector<Pi>, no repeated last)
 */
template <class T> double signed_area(const vector<Pt<T>> &p) {
  double s = 0;
  int n = p.size();
  for (int i = 0; i < n; i++)
    s += cross(p[i], p[(i + 1) % n]);
  return s / 2;
}
template <class T> double area(const vector<Pt<T>> &p) {
  return fabs(signed_area(p));
}
template <class T> bool is_ccw(const vector<Pt<T>> &p) {
  return signed_area(p) > 0;
}

/**
 * SHOELACE PREFIX SUMS — O(1) sub-polygon area queries on a convex polygon.
 *
 * Build: shoelace_prefix(pts) returns prefix[] of length n+1 where
 *   prefix[k] = cross(p0,p1) + cross(p1,p2) + ... + cross(p_{k-1},p_k)
 *
 * Query: 2 * signed_area of sub-polygon p_i, p_{i+1}, ..., p_j  (i < j) is:
 *   (prefix[j] - prefix[i]) + cross(p_j, p_i)
 *
 * The first term covers boundary edges i→i+1→...→j.
 * The second term closes the chord j→i.
 * Take abs() / 2 for unsigned area.
 *
 * For convex polygons this gives "ear area" = area between chord(i,j) and
 * boundary. Use long long (Pi) to avoid overflow with large coords.
 */
template <class T> vector<T> shoelace_prefix(const vector<Pt<T>> &p) {
  int n = p.size();
  vector<T> pre(n + 1, 0);
  for (int k = 0; k < n; k++)
    pre[k + 1] = pre[k] + cross(p[k], p[(k + 1) % n]);
  return pre;
}

// Area of sub-polygon p[i], p[i+1], ..., p[j] using precomputed prefix.
// Returns 2 * signed area (divide by 2 and take abs for unsigned area).
template <class T>
T subpoly_area2(const vector<T> &pre, const vector<Pt<T>> &p, int i, int j) {
  return (pre[j] - pre[i]) + cross(p[j], p[i]);
}

template <class T> double perimeter(const vector<Pt<T>> &p) {
  double s = 0;
  int n = p.size();
  for (int i = 0; i < n; i++)
    s += dist(p[i], p[(i + 1) % n]);
  return s;
}

inline P centroid(const vector<P> &p) {
  P c{0, 0};
  double A = 0;
  int n = p.size();
  for (int i = 0; i < n; i++) {
    double cr = cross(p[i], p[(i + 1) % n]);
    c = c + (p[i] + p[(i + 1) % n]) * cr;
    A += cr;
  }
  return c / (3 * A);
}

// 0 outside, 1 boundary, 2 inside.  Works for any simple polygon.
template <class T> int polygon_contains(const vector<Pt<T>> &poly, Pt<T> q) {
  int n = poly.size(), wn = 0;
  for (int i = 0; i < n; i++) {
    Pt<T> a = poly[i], b = poly[(i + 1) % n];
    if (point_on_segment(q, a, b))
      return 1;
    if (a.y <= q.y) {
      if (b.y > q.y && orient(a, b, q) > 0)
        wn++;
    } else {
      if (b.y <= q.y && orient(a, b, q) < 0)
        wn--;
    }
  }
  return wn ? 2 : 0;
}

template <class T> bool is_convex(const vector<Pt<T>> &p) {
  int n = p.size(), pos = 0, neg = 0;
  for (int i = 0; i < n; i++) {
    int o = orient(p[i], p[(i + 1) % n], p[(i + 2) % n]);
    if (o > 0)
      pos++;
    if (o < 0)
      neg++;
  }
  return !pos || !neg;
}

/**
 * CONVEX HULL — Andrew monotone chain, returns CCW, no duplicate endpoint.
 * strict=true (default): drop collinear points (only true vertices).
 * strict=false: keep collinear points on hull edges.
 */
template <class T>
vector<Pt<T>> convex_hull(vector<Pt<T>> p, bool strict = true) {
  sort(p.begin(), p.end());
  p.erase(unique(p.begin(), p.end()), p.end());
  int n = p.size(), k = 0;
  if (n < 3)
    return p;
  vector<Pt<T>> h(2 * n);
  auto bad = [&](Pt<T> a, Pt<T> b, Pt<T> c) {
    T x = cross(b - a, c - a);
    return strict ? x <= 0 : x < 0;
  };
  for (int i = 0; i < n; i++) {
    while (k >= 2 && bad(h[k - 2], h[k - 1], p[i]))
      k--;
    h[k++] = p[i];
  }
  for (int i = n - 2, t = k + 1; i >= 0; i--) {
    while (k >= t && bad(h[k - 2], h[k - 1], p[i]))
      k--;
    h[k++] = p[i];
  }
  h.resize(k - 1);
  return h;
}

/**
 * CIRCLES
 */
struct Circle {
  P c;
  double r;
};

inline int circle_line_intersect(Circle C, P a, P b, vector<P> &out) {
  P d = b - a, f = a - C.c;
  double A = dot(d, d), B = 2 * dot(f, d), Cc = dot(f, f) - C.r * C.r;
  double disc = B * B - 4 * A * Cc;
  if (disc < -EPS)
    return 0;
  disc = safe_sqrt(disc);
  double t1 = (-B - disc) / (2 * A), t2 = (-B + disc) / (2 * A);
  out.push_back(a + d * t1);
  if (disc > EPS)
    out.push_back(a + d * t2);
  return out.size();
}

inline int circle_circle_intersect(Circle A, Circle B, vector<P> &out) {
  P d = B.c - A.c;
  double d2 = dot(d, d), dlen = sqrt(d2);
  if (dlen < EPS)
    return 0; // concentric
  if (dlen > A.r + B.r + EPS || dlen + min(A.r, B.r) + EPS < max(A.r, B.r))
    return 0;
  double a = (A.r * A.r - B.r * B.r + d2) / (2 * dlen);
  double h = safe_sqrt(A.r * A.r - a * a);
  P p = A.c + d * (a / dlen);
  P n = rotate90(d) * (h / dlen);
  out.push_back(p + n);
  if (h > EPS)
    out.push_back(p - n);
  return out.size();
}

/**
 * ANGULAR SORT (no atan2 — exact for integer points)
 */
template <class T> int half(Pt<T> p) {
  // 0 = upper half (y > 0, or y == 0 && x > 0); 1 = lower half.
  return (p.y < 0 || (p.y == 0 && p.x < 0)) ? 1 : 0;
}
template <class T> bool polar_cmp(Pt<T> a, Pt<T> b) {
  int ha = half(a), hb = half(b);
  if (ha != hb)
    return ha < hb;
  T c = cross(a, b);
  if (c != 0)
    return c > 0;
  return norm2(a) < norm2(b); // tie: closer first
}

/**
 * POLYGON CUT — cut a convex/simple polygon by the line through a→b.
 * Keeps the left side (CCW from a to b).
 * Returns the resulting polygon as a vector of points (doubles).
 * O(N) per cut.
 */
inline vector<P> polygon_cut(const vector<P> &poly, P a, P b) {
  vector<P> res;
  int n = poly.size();
  for (int i = 0; i < n; i++) {
    P c = poly[i], d = poly[(i + 1) % n];
    double c1 = cross(b - a, c - a), c2 = cross(b - a, d - a);
    if (c1 >= -EPS)
      res.push_back(c);             // c is on left or on line
    if ((c1 > EPS) != (c2 > EPS)) { // c and d on different sides
      // Compute intersection of segment cd with line ab
      double t = cross(b - a, c - a) / cross(b - a, d - c);
      res.push_back(c + (d - c) * t);
    }
  }
  return res;
}

/**
 * MINKOWSKI SUM of two convex polygons P and Q (both CCW, no repeated last
 * vertex). Returns a convex polygon (CCW). O(N + M) where N = |P|, M = |Q|.
 */
inline vector<P> minkowski_sum(vector<P> P_poly, vector<P> Q_poly) {
  // Reorder so that the bottom-most (then left-most) point is first
  auto reorder = [](vector<P> &poly) {
    int idx = 0;
    for (int i = 1; i < (int)poly.size(); i++)
      if (poly[i].y < poly[idx].y ||
          (feq(poly[i].y, poly[idx].y) && poly[i].x < poly[idx].x))
        idx = i;
    rotate(poly.begin(), poly.begin() + idx, poly.end());
  };
  reorder(P_poly);
  reorder(Q_poly);

  int n = P_poly.size(), m = Q_poly.size();
  // Build edge vectors
  vector<P> edP(n), edQ(m);
  for (int i = 0; i < n; i++)
    edP[i] = P_poly[(i + 1) % n] - P_poly[i];
  for (int i = 0; i < m; i++)
    edQ[i] = Q_poly[(i + 1) % m] - Q_poly[i];

  vector<P> result;
  result.push_back(P_poly[0] + Q_poly[0]);
  int i = 0, j = 0;
  while (i < n || j < m) {
    P e;
    if (i < n && j < m) {
      double c = cross(edP[i], edQ[j]);
      if (c > EPS) {
        e = edP[i++];
      } else if (c < -EPS) {
        e = edQ[j++];
      } else {
        e = edP[i++] + edQ[j++];
      }
    } else if (i < n) {
      e = edP[i++];
    } else {
      e = edQ[j++];
    }
    result.push_back(result.back() + e);
  }
  result.pop_back(); // last point == first point
  return result;
}

/**
 * SIMPLE POLYGON FROM POINTS  (Kattis "simplepolygon" trick)
 * Pick lowest point as pivot, sort others by angle around it.
 * Returns indices into the input array.
 * NOTE: Reverses collinear points on the last ray to avoid self-intersection.
 */
template <class T> vector<int> make_simple_polygon(const vector<Pt<T>> &pts) {
  int n = pts.size(), piv = 0;
  for (int i = 1; i < n; i++)
    if (pts[i].y < pts[piv].y ||
        (pts[i].y == pts[piv].y && pts[i].x < pts[piv].x))
      piv = i;
  vector<int> idx;
  for (int i = 0; i < n; i++)
    if (i != piv)
      idx.push_back(i);
  Pt<T> O = pts[piv];
  sort(idx.begin(), idx.end(), [&](int i, int j) {
    Pt<T> a = pts[i] - O, b = pts[j] - O;
    T c = cross(a, b);
    if (c != 0)
      return c > 0;
    return norm2(a) < norm2(b);
  });

  // Reverse collinear points on the last ray to prevent polygon folding back
  if (!idx.empty()) {
    int last = idx.size() - 1;
    Pt<T> last_dir = pts[idx[last]] - O;
    while (last > 0) {
      Pt<T> prev_dir = pts[idx[last - 1]] - O;
      if (cross(last_dir, prev_dir) == 0)
        last--;
      else
        break;
    }
    reverse(idx.begin() + last, idx.end());
  }

  vector<int> ans = {piv};
  for (int i : idx)
    ans.push_back(i);
  return ans;
}

#pragma GCC optimize("O3")
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
#define print(rng, sz)                                                         \
  do {                                                                         \
    int _n = (sz);                                                             \
    for (int _i = 0; _i < _n; _i++)                                            \
      cout << (rng)[_i] << " \n"[_i == _n - 1];                                \
  } while (0)

const ll INF = 1e18;

void fast_io() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
}

void solve() {

  int n, q;
  cin >> n >> q;

  // cout << n << ' ' << q << '\n';;
  vector<Pt<ll>> targets(n);
  for (int i = 0; i < n; i++) {
    ll x, y;
    cin >> x >> y;
    targets[i] = Pt(x, y);
  }

  vector<Pt<ll>> eyes(q);
  for (int i = 0; i < q; i++) {
    ll x, y;
    cin >> x >> y;
    eyes[i] = Pt(x, y);
  }

  Pt<ll> fixed = Pt(0LL, (ll)1e18);

  // for (auto t : targets) cout << angle(fixed, t.first) << ' ';
  // cout << '\n';;
  // for (auto t : targets) cout << angle(fixed, t.first) << ' ';
  // cout << '\n';;

  map<Pt<ll>, int> mp;

  for (int i = 0; i < n; ++i) {
    mp[targets[i]] = i;
  }

  sort(targets.begin(), targets.end(), [&](const Pt<ll> &a, const Pt<ll> &b) {
    // Pt<ll> a = _a.first, b = _b.first;
    // double ta = angle(fixed, a);
    // double tb = angle(fixed, b);

    int ha = half(a), hb = half(b);
    if (ha != hb)
      return ha < hb;
    ll c = cross(a, b);
    return c > 0;
    // return norm2(a) < norm2(b); // tie: closer first
  });

  // for (auto t : targets) cout << angle(fixed, t.first) << ' ';
  // cout << '\n';;

  // for (auto t : eyes) cout << angle(fixed, t.first) << ' ';
  // cout << '\n';;

  for (auto eye : eyes) {
    if (eye.x == 0 && eye.y == 0) {
      cout << 1 << '\n';
      ;
      continue;
    }

    auto low = lower_bound(targets.begin(), targets.end(), eye,
                           [&](const Pt<ll> &a, const Pt<ll> &b) {
                             int ha = half(a), hb = half(b);
                             if (ha != hb)
                               return ha < hb;
                             ll c = cross(a, b);
                             return c > 0;
                           });

    // if (low == targets.end()) {
    //   low = targets.begin();
    // }
    // cout << low->second + 1 << '\n';;
    // continue;

    auto prev = low - 1;
    if (low == targets.begin())
      prev = targets.end() - 1;
    if (low == targets.end()) {
      prev = targets.end() - 1;
      low = targets.begin();
    }

    ll ldist = dist2(*low, eye);

    ll pdist = dist2(*prev, eye);

    if (ldist == pdist) {
      cout << min(mp[*low], mp[*prev]) + 1 << '\n';
    }

    else if (ldist < pdist) {
      cout << mp[*low] + 1 << '\n';

    } else {
      cout << mp[*prev] + 1 << '\n';
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
