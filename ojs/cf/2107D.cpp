#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
#define depth first
#define node second
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }
#ifdef ONLINE_JUDGE
#	define debug(args...) ((void) 0)
#else
#	define debug(args...) fprintf(stderr, args)
#endif

const int N = 212345;

vector<int> adj[N];
pii prev_ans[N];
int seen[N], sn;

struct tr {
    int d, u, v;
};

pii dfs(int u, int p) {
    vector<pii> all;
    for(int v : adj[u])
        if(v != p)
            all.pb(dfs(v, u));
    if(all.empty()) {
        prev_ans[u] = {0, u};
        return {0, u};
    }
    pii ans = *max_element(all.begin(), all.end());
    prev_ans[u] = {ans.depth + 1, ans.node};
    return prev_ans[u];
}

pii dfs2(int u, int p, int mx) {
    vector<pii> best, prev_a;
    for(int v : adj[u])
        if(v != p)
            best.pb(dfs2(v, u, mx)), prev_a.pb(prev_ans[v]);
    sort(prev_a.begin(), prev_a.end());
    reverse(prev_a.begin(), prev_a.end());
    if(u == p) {
        best.pb({max(u, prev_a.front().node), min(u, prev_a.front().node)});
        assert(best.back().fst !=best.back().snd);
    }
    if(prev_a.size() > 1 && prev_a[0].depth + prev_a[1].depth + 2 == mx) {
        vector<int> other;
        for(int i = 1; i < prev_a.size() && prev_a[i].depth == prev_a[1].depth; i++)
            other.pb(prev_a[i].node);
        if(prev_a[0].depth == prev_a[1].depth) {
            other.pb(prev_a[0].node);
            sort(other.begin(), other.end()); reverse(other.begin(), other.end());
            best.pb({other[0], other[1]});
            assert(best.back().fst!=best.back().snd);
        } else {
            int w = *max_element(other.begin(), other.end());
            best.pb({max(prev_a[0].node, w), min(prev_a[0].node, w)});
            assert(best.back().fst != best.back().snd);
        }
    }
    if(best.empty()) return {-1e9, -1e9};
    return *max_element(best.begin(), best.end());
}

bool dfs3(int u, int p, int v) {
    if(u == v) {
        seen[u] = sn;
        return true;
    }
    for(int w : adj[u])
        if(w != p && dfs3(w, u, v)) {
            seen[u] = sn;
            return true;
        }
    return false;
}

void dfs4(vector<int> &nodes, int u) {
    seen[u] = sn;
    nodes.pb(u);
    for(int v : adj[u])
        if(seen[v] < sn) {
            dfs4(nodes, v);
        }
}

vector<int> solve(vector<int> &nodes) {
    assert(!nodes.empty());
    if(nodes.size() == 1) {
        vector<int> ans;
        ans.pb(1); ans.pb(nodes[0]); ans.pb(nodes[0]);
        return ans;
    }
    int u = dfs(nodes[0], nodes[0]).node;
    int mx_path = dfs(u, u).depth;
    pii ans = dfs2(u, u, mx_path);
    debug("ans %d %d\n", ans.fst, ans.snd);
    vector<int> ret;
    ret.pb(mx_path + 1); ret.pb(ans.fst); ret.pb(ans.snd);
    sn++;
    dfs3(ans.fst, ans.fst, ans.snd);
    for(int u : nodes) {
        if(seen[u] == sn) continue;
        int i = 0;
        while(i < adj[u].size()) {
            if(seen[adj[u][i]] == sn) {
                swap(adj[u][i], adj[u].back());
                adj[u].pop_back();
            } else i++;
        }
    }
    vector<vector<int>> sub;
    vector<vector<int>> inner;
    vector<int> p;
    int k = 0;
    for(int u : nodes)
        if(seen[u] < sn) {
            vector<int> new_nodes;
            dfs4(new_nodes, u);
            sub.pb(new_nodes);
            p.pb(k++);
        }
    for(vector<int> &new_nodes: sub)
        inner.pb(solve(new_nodes));
    sort(p.begin(), p.end(), [&](int i, int j) { return inner[i] > inner[j]; });
    debug("p size %d\n", p.size());
    for(int i : p)
        for(int x : inner[i])
            ret.pb(x);
    return ret;
}

int main() {
    int i, a, b, n;
    for_tests(t, tt) {
        sn++;
        scanf("%d", &n);
        vector<int> nodes;
        for(i = 0; i < n; i++) nodes.pb(i + 1);
        for(i = 0; i < n - 1; i++) {
            scanf("%d %d", &a, &b);
            adj[a].pb(b);
            adj[b].pb(a);
        }
        vector<int> ans = solve(nodes);
        for(int x : ans)
            printf("%d ", x);
        putchar('\n');
        for(i = 0; i <= n; i++) adj[i].clear();
    }
}