#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }

const int N = 1123456;

vector<int> adj[N];
int orig_u[N], uv[N], t[N];
bool included[N];
int n, m;
bool is_odd[N];
int seen[N];
int odd_count[N];
int c[N];

// build tree, count odds in subtrees
int dfs1(int u) {
    seen[u] = 1;
    odd_count[u] = is_odd[u];
    for(int e : adj[u])
        if(t[e] == 0 && seen[uv[e] ^ u] == 0)
            odd_count[u] += dfs1(uv[e] ^ u);
    return odd_count[u];
}

// decide included edges from previous dfs tree
void dfs2(int u) {
    seen[u] = 2;
    for(int e : adj[u])
        if(t[e] == 0 && seen[uv[e] ^ u] < 2) {
            if(odd_count[uv[e] ^ u] & 1)
                included[e] = true;
            dfs2(uv[e] ^ u);
        }
}

// build cycles
void dfs3(int u) {
    while(!adj[u].empty()) {
        int e = adj[u].back(); adj[u].pop_back();
        if(!included[e]) continue;
        included[e] = false; // Don't use the reverse edge
        c[e] = orig_u[e] == u? 1 : -1;
        dfs3(uv[e] ^ u);
    }
}

void imp() {
    puts("N");
    exit(0);
}

int main() {
    ios_base::sync_with_stdio(false);
    scanf("%d %d", &n, &m);
    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d %d", &u, &v, &t[i]); u--; v--;
        orig_u[i] = u;
        included[i] = t[i] == 1;
        adj[u].pb(i);
        adj[v].pb(i);
        uv[i] = u ^ v;
        if (t[i] == 1) is_odd[u] ^= 1, is_odd[v] ^= 1;
    }
    for(int i = 0; i < n; i++) {
        if (seen[i] == 0) {
            if(dfs1(i) & 1) imp();
            dfs2(i);
        }
    }
    for(int i = 0; i < n; i++)
        dfs3(i);
    puts("S");
    for(int i = 0; i < m; i++)
        printf("%d%c", c[i], " \n"[i == m - 1]);
}
