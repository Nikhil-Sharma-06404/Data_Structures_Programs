#include <bits/stdc++.h>
using namespace std;

const int MAXN = 300005;
const int LOG = 20;  // Log base 2 of 300000

vector<int> adj[MAXN];
int up[MAXN][LOG], depth[MAXN], dist[MAXN];
int n;

void dfs(int v, int p) {
    up[v][0] = p;  // First ancestor is the parent
    for (int i = 1; i < LOG; i++) {
        if (up[v][i - 1] != -1) {
            up[v][i] = up[up[v][i - 1]][i - 1];
        }
    }
    for (int u : adj[v]) {
        if (u != p) {
            depth[u] = depth[v] + 1;
            dist[u] = dist[v] + 1;
            dfs(u, v);
        }
    }
}

int lca(int u, int v) {
    if (depth[u] < depth[v]) swap(u, v);
    // Lift u to the same level as v
    for (int i = LOG - 1; i >= 0; i--) {
        if (depth[u] - (1 << i) >= depth[v]) {
            u = up[u][i];
        }
    }
    if (u == v) return u;
    // Lift both u and v together
    for (int i = LOG - 1; i >= 0; i--) {
        if (up[u][i] != up[v][i]) {
            u = up[u][i];
            v = up[v][i];
        }
    }
    return up[u][0];
}

int count_valid_x(int d1, int d2) {
    int min_d = abs(d1 - d2) + 1;
    int max_d = d1 + d2 - 1;
    return max_d - min_d + 1;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int t;
    cin >> t;

    while (t--) {
        cin >> n;
        for (int i = 1; i <= n; i++) {
            adj[i].clear();
        }

        for (int i = 1; i < n; i++) {
            int u, v;
            cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        memset(up, -1, sizeof(up));
        depth[1] = 0;
        dist[1] = 0;
        dfs(1, -1);

        long long result = 0;

        for (int i = 1; i < n; i++) {
            for (int j = i + 1; j <= n; j++) {
                int LCA = lca(i, j);
                int dist_u = dist[i] - dist[LCA];
                int dist_v = dist[j] - dist[LCA];
                if (dist_u > 0 && dist_v > 0) {
                    result += count_valid_x(dist_u, dist_v);
                }
            }
        }

        cout << result << '\n';
    }

    return 0;
}
