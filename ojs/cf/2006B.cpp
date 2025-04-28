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

const int N = 212345;
int t, n;
ll w, det;
vector<int> adj[N];
int e[2][N];

int unknown_tot, unknown[N];

void dfs(int u, int &want) {
    if (u == want) want = (u + 1) % n;
    for(int v : adj[u]) {
        e[0][v] = want;
        unknown[want]++;
        dfs(v, want);
        e[1][v] = want;
        unknown[want]++;
        if (u == want) want = (u + 1) % n;
    }
}

int main() {
    scanf("%d", &t);
    while (t--) {
        scanf("%d %lld", &n, &w);
        unknown_tot = n; det = 0;
        for(int i = 1; i < n; i++) {
            int p;
            scanf("%d", &p);
            adj[p - 1].pb(i);
        }
        for(int i = 0; i < n; i++) sort(adj[i].begin(), adj[i].end());
        int want = 0;
        dfs(0, want);
        for(int i = 0; i < n - 1; i++) {
            int x; ll y;
            scanf("%d %lld", &x, &y);
            for(int k = 0; k < 2; k++)
                if (--unknown[e[k][x - 1]] == 0)
                    unknown_tot--;
            det += y;
            assert(det <= w); printf("%lld ", 2ll * det + ll(unknown_tot) * (w - det));
        }
        putchar('\n');
        for(int i = 0; i < n; i++)
            adj[i].clear(), unknown[i] = 0;
    }
    
}