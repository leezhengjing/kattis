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

namespace CPString {

// ------------------------------------------
// 1. KMP (Knuth-Morris-Pratt) & Prefix Function
// ------------------------------------------
// pi[i] = length of the longest proper prefix of s[0..i]
// that is also a suffix of s[0..i].
vi compute_pi(const string &P) {
  int m = P.length();
  vi pi(m, 0);
  for (int i = 1, j = 0; i < m; i++) {
    while (j > 0 && P[i] != P[j])
      j = pi[j - 1];
    if (P[i] == P[j])
      j++;
    pi[i] = j;
  }
  return pi;
}

// Returns all 0-indexed starting positions of pattern P in text T
vi kmp_search(const string &T, const string &P) {
  vi matches;
  if (P.empty() || T.empty() || P.length() > T.length())
    return matches;

  vi pi = compute_pi(P);
  int n = T.length(), m = P.length();

  for (int i = 0, j = 0; i < n; i++) {
    while (j > 0 && T[i] != P[j])
      j = pi[j - 1];
    if (T[i] == P[j])
      j++;
    if (j == m) {
      matches.push_back(i - m + 1);
      j = pi[j - 1]; // Reset to find overlapping matches
    }
  }
  return matches;
}

// ------------------------------------------
// 2. DOUBLE ROLLING HASH (Hack-proof)
// ------------------------------------------
// Uses two modulos to prevent deliberate collisions.
struct StringHash {
  const ll M1 = 1e9 + 7, B1 = 313;
  const ll M2 = 1e9 + 9, B2 = 317;
  vector<ll> h1, h2, p1, p2;

  StringHash(const string &s) {
    int n = s.length();
    h1.assign(n + 1, 0);
    h2.assign(n + 1, 0);
    p1.assign(n + 1, 1);
    p2.assign(n + 1, 1);

    for (int i = 0; i < n; ++i) {
      h1[i + 1] = (h1[i] * B1 + s[i]) % M1;
      p1[i + 1] = (p1[i] * B1) % M1;

      h2[i + 1] = (h2[i] * B2 + s[i]) % M2;
      p2[i + 1] = (p2[i] * B2) % M2;
    }
  }

  // Returns {hash1, hash2} for substring s[L...R] (0-indexed)
  pair<ll, ll> get_hash(int L, int R) {
    ll val1 = (h1[R + 1] - h1[L] * p1[R - L + 1]) % M1;
    if (val1 < 0)
      val1 += M1;

    ll val2 = (h2[R + 1] - h2[L] * p2[R - L + 1]) % M2;
    if (val2 < 0)
      val2 += M2;

    return {val1, val2};
  }
};

// ------------------------------------------
// 3. FLAT ARRAY TRIE (Fast, no memory leaks)
// ------------------------------------------
struct Trie {
  struct Node {
    int next[26];
    bool is_end = false;
    int prefix_count = 0;
    Node() { memset(next, -1, sizeof(next)); }
  };

  vector<Node> tree;

  Trie() { tree.emplace_back(); } // Root is at index 0

  void insert(const string &s) {
    int u = 0;
    for (char c : s) {
      int idx = c - 'a'; // Adjust to 'A' if uppercase
      if (tree[u].next[idx] == -1) {
        tree[u].next[idx] = tree.size();
        tree.emplace_back();
      }
      u = tree[u].next[idx];
      tree[u].prefix_count++;
    }
    tree[u].is_end = true;
  }

  bool search(const string &s) {
    int u = 0;
    for (char c : s) {
      int idx = c - 'a';
      if (tree[u].next[idx] == -1)
        return false;
      u = tree[u].next[idx];
    }
    return tree[u].is_end;
  }

  bool starts_with(const string &prefix) {
    int u = 0;
    for (char c : prefix) {
      int idx = c - 'a';
      if (tree[u].next[idx] == -1)
        return false;
      u = tree[u].next[idx];
    }
    return true;
  }
};

// ------------------------------------------
// 4. SUFFIX ARRAY + LCP + RMQ (O(N log N))
// ------------------------------------------
class SuffixArray {
private:
  void countingSort(int k) {
    int maxi = max(300, n);
    vi c(maxi, 0);
    for (int i = 0; i < n; ++i)
      ++c[i + k < n ? RA[i + k] : 0];
    for (int i = 0, sum = 0; i < maxi; ++i) {
      int t = c[i];
      c[i] = sum;
      sum += t;
    }
    vi tempSA(n);
    for (int i = 0; i < n; ++i)
      tempSA[c[SA[i] + k < n ? RA[SA[i] + k] : 0]++] = SA[i];
    swap(SA, tempSA);
  }

  void constructSA() {
    SA.resize(n);
    iota(SA.begin(), SA.end(), 0);
    RA.resize(n);
    for (int i = 0; i < n; ++i)
      RA[i] = T[i];
    for (int k = 1; k < n; k <<= 1) {
      countingSort(k);
      countingSort(0);
      vi tempRA(n);
      int r = 0;
      tempRA[SA[0]] = r;
      for (int i = 1; i < n; ++i) {
        tempRA[SA[i]] = ((RA[SA[i]] == RA[SA[i - 1]]) &&
                         (RA[SA[i] + k] == RA[SA[i - 1] + k]))
                            ? r
                            : ++r;
      }
      swap(RA, tempRA);
      if (RA[SA[n - 1]] == n - 1)
        break;
    }
  }

  void computeLCP() {
    vi Phi(n), PLCP(n);
    Phi[SA[0]] = -1;
    for (int i = 1; i < n; ++i)
      Phi[SA[i]] = SA[i - 1];
    for (int i = 0, L = 0; i < n; ++i) {
      if (Phi[i] == -1) {
        PLCP[i] = 0;
        continue;
      }
      while ((i + L < n) && (Phi[i] + L < n) && (T[i + L] == T[Phi[i] + L]))
        ++L;
      PLCP[i] = L;
      L = max(L - 1, 0);
    }
    LCP.resize(n);
    for (int i = 0; i < n; ++i)
      LCP[i] = PLCP[SA[i]];
  }

  // Builds the Sparse Table for O(1) Range Minimum Queries
  void buildRMQ() {
    int K = 0;
    while ((1 << K) <= n)
      K++;

    st.assign(K, vector<int>(n));
    log2_val.assign(n + 1, 0);

    for (int i = 2; i <= n; i++)
      log2_val[i] = log2_val[i / 2] + 1;
    for (int i = 0; i < n; i++)
      st[0][i] = LCP[i];

    for (int i = 1; i < K; i++) {
      for (int j = 0; j + (1 << i) <= n; j++) {
        st[i][j] = min(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);
      }
    }
  }

public:
  string T;
  int n;
  vi SA, LCP, RA;
  vector<vector<int>> st;
  vector<int> log2_val;

  SuffixArray(string initialT) {
    T = initialT;
    if (T.empty() || T.back() != '$')
      T += '$';
    n = T.length();
    constructSA();
    computeLCP();
    buildRMQ();
  }

  // O(1) query to find the Longest Common Prefix of any two original string
  // indices
  int get_lcp(int a, int b) {
    if (a == b)
      return n - 1 - a; // n includes '$', so n-1 is the original length

    int ra = RA[a];
    int rb = RA[b];
    if (ra > rb)
      swap(ra, rb);

    int L = ra + 1;
    int R = rb;
    int k = log2_val[R - L + 1];

    return min(st[k][L], st[k][R - (1 << k) + 1]);
  }

  ii LRS() {
    int idx = 0, maxLCP = -1;
    for (int i = 1; i < n; ++i) {
      if (LCP[i] > maxLCP) {
        maxLCP = LCP[i];
        idx = i;
      }
    }
    return {maxLCP, idx};
  }

  ii LCS(int split_idx) {
    int idx = 0, maxLCP = -1;
    for (int i = 1; i < n; ++i) {
      if ((SA[i] < split_idx) == (SA[i - 1] < split_idx))
        continue;
      if (LCP[i] > maxLCP) {
        maxLCP = LCP[i];
        idx = i;
      }
    }
    return {maxLCP, idx};
  }
};

// ------------------------------------------
// 5. STRING ALIGNMENT (Needleman-Wunsch DP)
// ------------------------------------------
// Match = +2, Mismatch = -1, Gap (Insert/Delete) = -1
int string_alignment(const string &A, const string &B) {
  int n = A.length(), m = B.length();
  vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

  for (int i = 1; i <= n; i++)
    dp[i][0] = i * -1;
  for (int j = 1; j <= m; j++)
    dp[0][j] = j * -1;

  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      dp[i][j] = dp[i - 1][j - 1] + (A[i - 1] == B[j - 1] ? 2 : -1);
      dp[i][j] = max(dp[i][j], dp[i - 1][j] - 1); // Delete
      dp[i][j] = max(dp[i][j], dp[i][j - 1] - 1); // Insert
    }
  }
  return dp[n][m];
}

} // namespace CPString

string L, S;

char edges[] = {'A', 'G', 'C', 'T'};
void solve() {
  int t1 = 0, t2 = 0, t3 = 0;
  int n = L.size();
  int m = S.size();

  t1 = CPString::kmp_search(L, S).size();

  unordered_set<string> seen;

  for (int i = 0; i < m; ++i) {
    string temp;

    if (i == 0) {
      temp = S.substr(i + 1);
    } else if (i == m - 1) {
      temp = S.substr(0, m - 1);
    } else {
      temp = S.substr(0, i) + S.substr(i + 1);
    }

    if (!seen.count(temp))
      t2 += CPString::kmp_search(L, temp).size();

    seen.insert(temp);
  }

  for (int i = 0; i <= m; ++i) {
    string temp;

    for (int j = 0; j < 4; ++j) {

      if (i == 0) {
        temp = edges[j] + S;
      } else if (i == m) {
        temp = S + edges[j];
      } else {
        temp = S.substr(0, i) + edges[j] + S.substr(i);
      }

      if (!seen.count(temp))
        t3 += CPString::kmp_search(L, temp).size();

      seen.insert(temp);
    }
  }

  cout << t1 << " " << t2 << " " << t3 << "\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;

  while (cin >> S >> L) {
    solve();
  }

  return 0;
}
