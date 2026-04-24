#include <bits/stdc++.h>
// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/tree_policy.hpp>
using namespace std;
// using namespace __gnu_pbds;

typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<vi> vvi;

#define LSOne(S) ((S) & -(S))
// int two_pow_p1 = LSOne(mask);
// int p1 = __builtin_ctz(two_pow_p1);
#define REP(i, s, t) for (int i = (s); i < (t); ++i)

template <class T> T read() {
  T v;
  std::cin >> v;
  return v;
}

void fast_io() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
}

int MOD;

template <typename T> void matmul(vector<vector<T>> &a, vector<vector<T>> b) {
  int n = a.size(), m = a[0].size(), p = b[0].size();
  assert(m == b.size());
  vector<vector<T>> c(n, vector<T>(p));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < p; j++) {
      for (int k = 0; k < m; k++) {
        ll term = (a[i][k] * b[k][j]) % MOD;
        c[i][j] = (c[i][j] + term + MOD) % MOD;
      }
    }
  }

  a = c;
}

template <typename T> struct Matrix {
  vector<vector<T>> mat;
  Matrix() {}
  Matrix(vector<vector<T>> a) { mat = a; }
  Matrix(int n, int m) {
    mat.resize(n);
    for (int i = 0; i < n; i++) {
      mat[i].resize(m);
    }
  }

  int rows() const { return mat.size(); }
  int cols() const { return mat[0].size(); }

  // makes the identity matrix for a n by n matrix
  void makeiden() {
    for (int i = 0; i < rows(); i++) {
      mat[i][i] = 1;
    }
  }

  void print() const {
    for (int i = 0; i < rows(); i++) {
      for (int j = 0; j < cols(); j++) {
        cout << mat[i][j] << ' ';
      }
      cout << '\n';
    }
  }

  Matrix operator*=(const Matrix &b) {
    matmul(mat, b.mat);
    return *this;
  }

  Matrix operator*(const Matrix &b) { return Matrix(*this) *= b; }
};

void solve() {
  // cin.ignore(numeric_limits<streamsize>::max(), '\n');
  int N;
  cin >> N;

  Matrix<ll> base_mat(N + 1, N + 1), vec(N + 1, 1);

  for (int i = 0; i <= N; ++i) {
    if (i == 0)
      cin >> vec.mat[N][0];
    else
      cin >> base_mat.mat[N - 1][N - i];
  }

  for (int i = 0; i < N; ++i) {
    cin >> vec.mat[i][0];
  }

  for (int i = 1; i <= N; ++i) {
    base_mat.mat[i - 1][i] = 1;
  }
  base_mat.mat[N][N] = 1;
  // vec.print();
  // base_mat.print();
  // cur.print();

  int Q;
  cin >> Q;

  for (int i = 0; i < Q; ++i) {
    ll T;
    cin >> T >> MOD;

    Matrix<ll> curr(N + 1, N + 1);
    curr.makeiden();

    Matrix<ll> mat = base_mat;
    while (T > 0) {
      if (T & 1)
        curr *= mat;
      mat *= mat;
      T >>= 1;
    }

    Matrix<ll> res = curr * vec;
    cout << res.mat[0][0] << "\n";
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
