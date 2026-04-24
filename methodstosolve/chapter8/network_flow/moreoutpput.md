Here is the complete, ready-to-submit C++ code for **Waif Until Dark (`waif`)**.

As we discussed, this problem is all about cleanly managing a 4-layer graph. To prevent the node indexing from turning into a nightmare of `+ N` and `+ M` offsets, I highly recommend using C++ lambda functions (like `get_child`, `get_toy`, and `get_cat`) to calculate the exact node IDs dynamically. It makes your graph modeling perfectly readable.

### Full Solution: `waif`

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef pair<int, int> ii;
typedef tuple<int, ll, ll> edge;

const ll INF = 1e18;

void fast_io() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
}

// --- FULLY PATCHED MAX FLOW TEMPLATE ---
class MaxFlow {
private:
    int V;
    vector<edge> EL;
    vector<vi> AL;
    vi d, last;
    vector<ii> p;

    bool BFS(int s, int t) {
        d.assign(V, -1);
        d[s] = 0;
        queue<int> q;
        q.push(s);
        p.assign(V, {-1, -1});

        while (!q.empty()) {
            int u = q.front();
            q.pop();
            if (u == t) break;

            for (auto &idx : AL[u]) {
                auto &[v, cap, flow] = EL[idx];
                if ((cap - flow > 0) && (d[v] == -1)) {
                    d[v] = d[u] + 1;
                    q.push(v);
                    p[v] = {u, idx};
                }
            }
        }
        return d[t] != -1;
    }

    ll send_one_flow(int s, int t, ll f = INF) {
        if (s == t) return f;
        auto &[u, idx] = p[t];
        auto &cap = get<1>(EL[idx]), &flow = get<2>(EL[idx]);
        ll pushed = send_one_flow(s, u, min(f, cap - flow));
        flow += pushed;
        auto &rflow = get<2>(EL[idx ^ 1]);
        rflow -= pushed;
        return pushed;
    }

    ll DFS(int u, int t, ll f = INF) {
        if ((u == t) || (f == 0)) return f;

        for (int &i = last[u]; i < (int)AL[u].size(); ++i) {
            int idx = AL[u][i];
            auto &[v, cap, flow] = EL[idx];

            if (d[v] != d[u] + 1) continue;

            if (ll pushed = DFS(v, t, min(f, cap - flow))) {
                flow += pushed;
                auto &rflow = get<2>(EL[idx ^ 1]);
                rflow -= pushed;
                return pushed;
            }
        }
        return 0;
    }

public:
    MaxFlow(int initialV) : V(initialV) {
        EL.clear();
        AL.assign(V, vi());
    }

    void add_edge(int u, int v, ll w, bool directed = true) {
        EL.emplace_back(v, w, 0);
        AL[u].push_back(EL.size() - 1);
        EL.emplace_back(u, directed ? 0 : w, 0);
        AL[v].push_back(EL.size() - 1);
    }

    ll dinic(int s, int t) {
        ll mf = 0;
        while (BFS(s, t)) {
            last.assign(V, 0);
            while (ll f = DFS(s, t))
                mf += f;
        }
        return mf;
    }
};
// ---------------------------------------

void solve() {
    int n, m, p;
    // Read number of children, toys, and categories
    if (!(cin >> n >> m >> p)) return;

    // --- NODE OFFSET MAPPING ---
    int S = 0;
    int T = 1;

    // Lambdas to cleanly get node indices.
    // 1-based indexing from the problem is preserved in the function arguments.
    auto get_child = [&](int i) { return 1 + i; }; // Children nodes: 2 to 1 + n
    auto get_toy   = [&](int i) { return 1 + n + i; }; // Toy nodes: 2 + n to 1 + n + m
    auto get_cat   = [&](int i) { return 1 + n + m + i; }; // Category nodes: 2 + n + m to 1 + n + m + p

    // Total nodes = 2 (S & T) + n (children) + m (toys) + p (categories)
    int total_nodes = 2 + n + m + p;
    MaxFlow mf(total_nodes);

    // 1. Source -> Children, and Children -> Toys
    for (int i = 1; i <= n; ++i) {
        // Each child can only play with 1 toy maximum
        mf.add_edge(S, get_child(i), 1, true);

        int k; cin >> k;
        for (int j = 0; j < k; ++j) {
            int t; cin >> t;
            // Child likes this toy, capacity 1
            mf.add_edge(get_child(i), get_toy(t), 1, true);
        }
    }

    // Keep track of which toys belong to a category so we can handle the uncategorized ones later
    vector<bool> has_category(m + 1, false);

    // 2. Toys -> Categories, and Categories -> Sink
    for (int i = 1; i <= p; ++i) {
        int l; cin >> l;
        for (int j = 0; j < l; ++j) {
            int t; cin >> t;
            has_category[t] = true;
            // Connect the toy to its specific category
            mf.add_edge(get_toy(t), get_cat(i), 1, true);
        }
        int r; cin >> r;
        // The bottleneck: Category can only provide 'r' toys to the sink!
        mf.add_edge(get_cat(i), T, r, true);
    }

    // 3. Uncategorized Toys -> Sink
    for (int i = 1; i <= m; ++i) {
        if (!has_category[i]) {
            // Uncategorized toys have no category bottlenecks, so they connect directly to T
            mf.add_edge(get_toy(i), T, 1, true);
        }
    }

    // 4. Run the algorithm!
    ll max_children_satisfied = mf.dinic(S, T);
    cout << max_children_satisfied << "\n";
}

int main() {
    fast_io();
    // The problem might have multiple test cases implicitly, so we loop
    int t = 1;
    // cin >> t; // Uncomment if the problem starts giving an explicit T variable
    while (cin >> ws && !cin.eof()) {
        solve();
    }
    return 0;
}

```

### Key Takeaway for Graph Building

Take a look at how we handled the `Uncategorized Toys`. When a problem gives you a generic rule ("Toys can be in at most one category") and then a silent exception ("any toy not listed... all of them can be used"), you have to build a bypass.

By routing the uncategorized toys directly to the Super-Sink `T` with a capacity of `1`, we effectively say, "This toy bypasses the wear-and-tear category restrictions."

Would you like me to drop the code for `piano` next, so you can see how to build the graph, run Dinic, _clear it_, and rebuild it to test the weekday vs. weekend condition?
These are fantastic problems. They move beyond basic matching and test your ability to use **Node Capacities** and **Multi-Stage Flows**.

Here is the C++ code for **Moving Pianos** and **Cops and Robbers**, using the fully patched `MaxFlow` template we built.

### 1. Moving Pianos (`piano`)

This problem requires checking two different states: one where tuners only work weekdays, and one where they work weekends. We build the graph twice to check both scenarios.

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> ii;
typedef tuple<int, ll, ll> edge;
const ll INF = 1e18;

// [PASTE THE MAX FLOW TEMPLATE CLASS HERE]
class MaxFlow {
    int V; vector<edge> EL; vector<vi> AL; vi d, last; vector<ii> p;
    bool BFS(int s, int t) {
        d.assign(V, -1); d[s] = 0; queue<int> q({s}); p.assign(V, {-1, -1});
        while (!q.empty()) {
            int u = q.front(); q.pop(); if (u == t) break;
            for (auto &idx : AL[u]) {
                auto &[v, cap, flow] = EL[idx];
                if ((cap - flow > 0) && (d[v] == -1))
                    d[v] = d[u] + 1, q.push(v), p[v] = {u, idx};
            }
        }
        return d[t] != -1;
    }
    ll DFS(int u, int t, ll f = INF) {
        if ((u == t) || (f == 0)) return f;
        for (int &i = last[u]; i < (int)AL[u].size(); ++i) {
            int idx = AL[u][i]; auto &[v, cap, flow] = EL[idx];
            if (d[v] != d[u] + 1) continue;
            if (ll pushed = DFS(v, t, min(f, cap - flow))) {
                flow += pushed; get<2>(EL[idx ^ 1]) -= pushed; return pushed;
            }
        }
        return 0;
    }
public:
    MaxFlow(int initialV) : V(initialV) { EL.clear(); AL.assign(V, vi()); }
    void add_edge(int u, int v, ll w, bool directed = true) {
        EL.emplace_back(v, w, 0); AL[u].push_back(EL.size() - 1);
        EL.emplace_back(u, directed ? 0 : w, 0); AL[v].push_back(EL.size() - 1);
    }
    ll dinic(int s, int t) {
        ll mf = 0; while (BFS(s, t)) { last.assign(V, 0); while (ll f = DFS(s, t)) mf += f; }
        return mf;
    }
};

void solve() {
    int m, p;
    if (!(cin >> m >> p)) return;

    vector<pair<int, int>> orders(m);
    int max_day = 0;
    for (int i = 0; i < m; ++i) {
        cin >> orders[i].first >> orders[i].second;
        max_day = max(max_day, orders[i].second);
    }

    int S = 0, T = 1;
    auto get_piano = [&](int i) { return 2 + i; };
    auto get_day = [&](int d) { return 2 + m + d - 1; }; // 1-indexed days
    int total_nodes = 2 + m + max_day;

    int tuners_per_day = p / 2;

    // Helper to build the graph and run flow
    auto check_flow = [&](bool include_weekends) {
        MaxFlow mf(total_nodes);
        for (int i = 0; i < m; ++i) {
            mf.add_edge(S, get_piano(i), 1); // 1 piano = 1 move
            for (int d = orders[i].first; d <= orders[i].second; ++d) {
                mf.add_edge(get_piano(i), get_day(d), 1);
            }
        }
        for (int d = 1; d <= max_day; ++d) {
            bool is_weekend = (d % 7 == 6 || d % 7 == 0);
            if (!is_weekend || include_weekends) {
                mf.add_edge(get_day(d), T, tuners_per_day);
            }
        }
        return mf.dinic(S, T);
    };

    if (check_flow(false) == m) cout << "fine\n";
    else if (check_flow(true) == m) cout << "weekend work\n";
    else cout << "serious trouble\n";
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int t; if (cin >> t) while (t--) solve();
    return 0;
}

```

---

### 2. Cops and Robbers (`copsandrobbers`)

This problem is a classic **Node Splitting** graph. Because you place barricades _inside_ the cells, the capacities belong to the nodes, not the edges between them. We split every grid cell $(r, c)$ into an `IN` node and an `OUT` node, and connect them with the cost of the barricade.

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> ii;
typedef tuple<int, ll, ll> edge;
const ll INF = 1e18; // Use a large number to represent infinity/unblockable

// [PASTE THE EXACT SAME MAX FLOW TEMPLATE CLASS HERE]

void solve() {
    int M_cols, N_rows, C;
    if (!(cin >> M_cols >> N_rows >> C)) return;

    vector<string> grid(N_rows);
    for (int i = 0; i < N_rows; ++i) cin >> grid[i];

    vector<ll> costs(C);
    for (int i = 0; i < C; ++i) cin >> costs[i];

    int S = 0, T = 1;
    // Node indexing helper
    auto IN = [&](int r, int c) { return 2 + 2 * (r * M_cols + c); };
    auto OUT = [&](int r, int c) { return 2 + 2 * (r * M_cols + c) + 1; };

    int total_nodes = 2 + 2 * (N_rows * M_cols);
    MaxFlow mf(total_nodes);

    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};

    for (int r = 0; r < N_rows; ++r) {
        for (int c = 0; c < M_cols; ++c) {
            char cell = grid[r][c];
            ll cell_cost = 0;

            if (cell == 'B' || cell == '.') cell_cost = INF; // Cannot barricade
            else cell_cost = costs[cell - 'a'];

            // 1. Node Capacity (IN -> OUT)
            mf.add_edge(IN(r, c), OUT(r, c), cell_cost);

            // If it's the bank, it's our Source.
            if (cell == 'B') mf.add_edge(S, IN(r, c), INF);

            // If the cell is on the border, robbers can escape directly to the Sink
            if (r == 0 || r == N_rows - 1 || c == 0 || c == M_cols - 1) {
                mf.add_edge(OUT(r, c), T, INF);
            }

            // 2. Connect to neighbors (OUT of current -> IN of neighbor)
            for (int i = 0; i < 4; ++i) {
                int nr = r + dr[i];
                int nc = c + dc[i];
                if (nr >= 0 && nr < N_rows && nc >= 0 && nc < M_cols) {
                    mf.add_edge(OUT(r, c), IN(nr, nc), INF);
                }
            }
        }
    }

    ll min_cost = mf.dinic(S, T);

    // If the cost is >= INF, it means the Bank was on the edge, or
    // there was a path of '.' cells leading entirely to the edge.
    if (min_cost >= INF) cout << "-1\n";
    else cout << min_cost << "\n";
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    solve();
    return 0;
}

```

Would you like me to map out the graph construction for _The Darkness_, which adds a layer of complexity by forcing you to calculate distance formulas before creating the S-T Min-Cut?
