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
char s[N];
vector<int> adj[N];
int mid, uleaf, ct1, ct0;

void dfs(int u, int p) {
    for(int v : adj[u])
        if(v != p) {
            if(adj[v].size() == 1) {
                if(s[v] == '?') uleaf++;
                else if(s[v] == '1') ct1++;
                else ct0++;
            } else if(s[v] == '?') mid++;
            dfs(v, u);
        }
}

int main() {
    scanf("%d", &t);
    while(t--) {
        scanf("%d", &n);
        mid = uleaf = ct1 = ct0 = 0;
        for(int i = 0; i < n - 1; i++) {
            int u, v;
            scanf("%d %d", &u, &v);
            adj[u - 1].pb(v - 1);
            adj[v - 1].pb(u - 1);
        }
        scanf("%s", s);
        dfs(0, 0);
        int ans = 0;
        if (s[0] == '?') {
            ans = max(ct1, ct0) + uleaf / 2;
            if(mid & 1) {
                ans = max(ans, min(ct0, ct1) + (uleaf + 1) / 2);
            }
        } else {
            ans = s[0] == '1' ? ct0 : ct1;
            ans += (uleaf + 1) / 2;
        }
        printf("%d\n", ans);
        for(int i = 0; i < n; i++) adj[i].clear();
    }

}