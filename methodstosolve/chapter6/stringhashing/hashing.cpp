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

namespace CPString { // v685j

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
// 3B. STATIC ARRAY TRIE (Ultimate Speed for 10^5+ nodes)
// ------------------------------------------
template <int MAX_NODES = 2500000, char BASE_CHAR = 'A', int ALPHABET = 26>
struct FastTrie {
  int next_node[MAX_NODES][ALPHABET];
  int word_count[MAX_NODES];
  int prefix_count[MAX_NODES];
  int node_cnt;

  FastTrie() { clear(); }

  void clear() {
    node_cnt = 1; // Index 0 is the root
    memset(next_node[0], -1, sizeof(next_node[0]));
    word_count[0] = false;
    prefix_count[0] = 0;
  }

  void insert(const string &s) {
    int u = 0;
    for (char c : s) {
      int idx = c - BASE_CHAR;
      if (next_node[u][idx] == -1) {
        memset(next_node[node_cnt], -1, sizeof(next_node[node_cnt]));
        word_count[node_cnt] = 0;
        prefix_count[node_cnt] = 0;
        next_node[u][idx] = node_cnt++;
      }
      u = next_node[u][idx];
      prefix_count[u]++;
    }
    word_count[u]++;
  }

  int get_node(const string &prefix) {
    int u = 0;
    for (char c : prefix) {
      int idx = c - BASE_CHAR;
      if (next_node[u][idx] == -1)
        return 0;
      u = next_node[u][idx];
    }
    return u;
  }

  bool search(const string &s) {
    int u = get_node(s);
    return u != 0 && word_count[u] > 0;
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
  bool search_pattern(const string &P) {
    int m = P.length();
    if (m == 0)
      return true;

    int l = 0, r = n - 1;
    while (l <= r) {
      int mid = l + (r - l) / 2;
      // Compare pattern with the prefix of the current suffix
      string suffix_prefix = T.substr(SA[mid], min(m, n - SA[mid]));

      if (suffix_prefix == P)
        return true;
      if (suffix_prefix < P) {
        l = mid + 1;
      } else {
        r = mid - 1;
      }
    }
    return false;
  }
  // O(N) Counts the total number of UNIQUE substrings in the string
  ll count_unique_substrings() {
    ll total = 0;
    // Note: n includes the appended '$', so original length is n - 1
    for (int i = 1; i < n; ++i) {
      // Length of suffix SA[i] excluding '$' is (n - 1) - SA[i]
      total += (n - 1 - SA[i]) - LCP[i];
    }
    return total;
  }

  // O(N) Counts the total number of UNIQUE REPEATED substrings (appears >= 2
  // times)
  ll count_unique_repeated_substrings() {
    ll total = 0;
    for (int i = 1; i < n; ++i) {
      if (LCP[i] > LCP[i - 1]) {
        total += (LCP[i] - LCP[i - 1]);
      }
    }
    return total;
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

// ------------------------------------------
// 6. PALINDROME UTILITIES
// ------------------------------------------

// O(N) Two-pointer check for full string palindrome
bool is_palindrome(const string &s) {
  int l = 0, r = s.length() - 1;
  while (l < r) {
    if (s[l++] != s[r--])
      return false;
  }
  return true;
}

// O(log N) Overflow-safe mathematical check for a number in a specific base
bool is_palindrome_base(ll n, ll base) {
  ll temp = n;
  ll reversed_n = 0;
  while (temp > 0) {
    reversed_n = reversed_n * base + (temp % base);
    temp /= base;
  }
  return reversed_n == n;
}

const string morse_alpha[26] = {
    ".-",   "-...", "-.-.", "-..",  ".",   "..-.", "--.",  "....", "..",
    ".---", "-.-",  ".-..", "--",   "-.",  "---",  ".--.", "--.-", ".-.",
    "...",  "-",    "..-",  "...-", ".--", "-..-", "-.--", "--.."};

const string morse_digit[10] = {"-----", ".----", "..---", "...--", "....-",
                                ".....", "-....", "--...", "---..", "----."};

// O(N) Manacher's Algorithm.
// Returns the actual longest palindromic substring.
string longest_palindrome(const string &s) {
  if (s.empty())
    return "";

  // Transform string to handle even-length palindromes safely
  // "aba" -> "^#a#b#a#$"
  string t = "^#";
  for (char c : s) {
    t += c;
    t += '#';
  }
  t += "$";

  int n = t.length();
  vi p(n, 0); // p[i] = radius of longest palindrome centered at i
  int C = 0,
      R = 0; // Center and Right edge of the furthest expanding palindrome

  int max_len = 0, best_center = 0;

  for (int i = 1; i < n - 1; i++) {
    int i_mirror = 2 * C - i; // Reflection of i across center C

    // If inside the right bound, initialize with mirrored value
    if (R > i) {
      p[i] = min(R - i, p[i_mirror]);
    }

    // Expand palindrome centered at i
    while (t[i + 1 + p[i]] == t[i - 1 - p[i]]) {
      p[i]++;
    }

    // Update center if expanded past current right bound
    if (i + p[i] > R) {
      C = i;
      R = i + p[i];
    }

    // Track the absolute longest palindrome found
    if (p[i] > max_len) {
      max_len = p[i];
      best_center = i;
    }
  }

  // Extract original string using the length and center
  int start_idx = (best_center - 1 - max_len) / 2;
  return s.substr(start_idx, max_len);
}

// ------------------------------------------
// 7. ANAGRAM UTILITIES
// ------------------------------------------

// O(N) Check if two strings are exact anagrams
bool is_anagram(const string &a, const string &b) {
  if (a.length() != b.length())
    return false;

  vector<int> freq(26, 0);
  // Assumes lowercase a-z. Adjust indexing for other character sets.
  for (int i = 0; i < a.length(); ++i) {
    freq[a[i] - 'a']++;
    freq[b[i] - 'a']--;
  }

  for (int f : freq) {
    if (f != 0)
      return false;
  }
  return true;
}

// O(N * M log M) Groups anagrams together from a list of words
vector<vector<string>> group_anagrams(const vector<string> &words) {
  unordered_map<string, vector<string>> groups;
  for (const string &w : words) {
    string key = w;
    sort(key.begin(), key.end()); // Sorting creates a unique "signature"
    groups[key].push_back(w);
  }

  vector<vector<string>> res;
  for (auto &pair : groups) {
    res.push_back(pair.second);
  }
  return res;
}

// O(N) Sliding Window: Finds all starting indices of pattern's anagrams in text
vi sliding_window_anagrams(const string &text, const string &pat) {
  vi res;
  if (text.length() < pat.length())
    return res;

  vector<int> p_freq(26, 0), window(26, 0);
  for (char c : pat)
    p_freq[c - 'a']++;

  int len = pat.length();
  for (int i = 0; i < text.length(); ++i) {
    // Add current character to window
    window[text[i] - 'a']++;

    // Remove the character that fell off the left side of the window
    if (i >= len) {
      window[text[i - len] - 'a']--;
    }

    // Once the window is fully formed, compare it
    if (i >= len - 1 && window == p_freq) {
      res.push_back(i - len + 1); // Push the starting index
    }
  }
  return res;
}
bool check_multigram(const string &s, int n, int L) {
  // Count frequencies for the target root (the first L characters)
  vector<int> target_freq(26, 0);
  for (int i = 0; i < L; ++i) {
    target_freq[s[i] - 'a']++;
  }

  // Check all subsequent chunks of length L
  for (int i = L; i < n; i += L) {
    vector<int> chunk_freq(26, 0);

    for (int j = 0; j < L; ++j) {
      chunk_freq[s[i + j] - 'a']++;
    }

    // If the frequencies don't match, it's not a valid multigram root
    if (chunk_freq != target_freq) {
      return false;
    }
  }

  return true;
}
// ------------------------------------------
// 8. Z-ALGORITHM
// ------------------------------------------
// z[i] is the length of the longest substring starting from s[i]
// which is also a prefix of s.
vi compute_z(const string &s) {
  int n = s.length();
  vi z(n, 0);
  for (int i = 1, l = 0, r = 0; i < n; ++i) {
    if (i <= r)
      z[i] = min(r - i + 1, z[i - l]);
    while (i + z[i] < n && s[z[i]] == s[i + z[i]])
      ++z[i];
    if (i + z[i] - 1 > r) {
      l = i;
      r = i + z[i] - 1;
    }
  }
  return z;
}

// O(N + M) Pattern matching using Z-Algorithm
// Puts pattern at front: P + "$" + T
vi z_search(const string &T, const string &P) {
  vi matches;
  if (P.empty() || T.empty() || P.length() > T.length())
    return matches;
  string concat = P + "$" + T;
  vi z = compute_z(concat);

  int m = P.length();
  for (int i = m + 1; i < concat.length(); ++i) {
    if (z[i] == m) {
      matches.push_back(i - (m + 1));
    }
  }
  return matches;
}

// ------------------------------------------
// 9. AHO-CORASICK (Multi-Pattern Matching)
// ------------------------------------------
struct AhoCorasick {
  struct Node {
    int next[26];
    int link = -1; // Failure link
    vi out;        // Indices of patterns that end here
    Node() { memset(next, -1, sizeof(next)); }
  };

  vector<Node> t;
  AhoCorasick() { t.emplace_back(); }

  // Insert a pattern and its ID (e.g., its index in your pattern array)
  void insert(const string &s, int id) {
    int u = 0;
    for (char c : s) {
      int idx = c - 'a'; // Adjust base char if needed
      if (t[u].next[idx] == -1) {
        t[u].next[idx] = t.size();
        t.emplace_back();
      }
      u = t[u].next[idx];
    }
    t[u].out.push_back(id);
  }

  // Build failure links using BFS
  void build() {
    queue<int> q;
    for (int c = 0; c < 26; c++) {
      if (t[0].next[c] != -1) {
        t[t[0].next[c]].link = 0;
        q.push(t[0].next[c]);
      } else {
        t[0].next[c] = 0;
      }
    }
    while (!q.empty()) {
      int u = q.front();
      q.pop();
      for (int c = 0; c < 26; c++) {
        if (t[u].next[c] != -1) {
          int v = t[u].next[c];
          t[v].link = t[t[u].link].next[c];
          // Merge output of failure link into current node
          t[v].out.insert(t[v].out.end(), t[t[v].link].out.begin(),
                          t[t[v].link].out.end());
          q.push(v);
        } else {
          t[u].next[c] = t[t[u].link].next[c];
        }
      }
    }
  }

  // Returns an array where ans[i] is a list of starting indices
  // where the i-th pattern appears in the text.
  vector<vi> search(const string &text, int num_patterns) {
    vector<vi> res(num_patterns);
    int u = 0;
    for (int i = 0; i < text.length(); i++) {
      u = t[u].next[text[i] - 'a'];
      for (int id : t[u].out) {
        // We know pattern 'id' ends at index 'i' in the text.
        // To get the start index, you can subtract pattern length.
        // For simplicity, we just store the ending index here,
        // or you can pass pattern lengths to store start indices.
        res[id].push_back(i);
      }
    }
    return res;
  }
};

} // namespace CPString

void fast_io() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
}

void solve() {
  string s;
  cin >> s;

  int q;
  cin >> q;
  CPString::StringHash sh(s);

  while (q--) {
    int L, R;
    cin >> L >> R;

    auto hash_pair = sh.get_hash(L, R - 1);

    unsigned long long combined_hash =
        ((unsigned long long)hash_pair.first << 32) | hash_pair.second;

    cout << combined_hash << "\n";
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
