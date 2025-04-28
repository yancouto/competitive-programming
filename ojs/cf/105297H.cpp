#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<ll, int> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }

#define N 212345

int n, m, t;

vector<int> adj[N];

int ab[N], x[N], y[N];
bool seen[N];


int main() {
    scanf("%d %d %d", &n, &m, &t);
    for(int i = 0; i < m; i++) {
        int a, b;
        scanf("%d %d %d %d", &a, &b, &x[i], &y[i]);
        a--; b--;
        adj[a].pb(i);
        adj[b].pb(i);
        ab[i] = a ^ b;
    }
    priority_queue<pii> pq;
    pq.push(pii(-t, 0));
    while(!pq.empty()) {
        pii p = pq.top(); pq.pop();
        if (seen[p.snd]) continue;
        seen[p.snd] = true;
        //printf("%d with %lld\n", p.snd, -p.fst);
        if (p.snd == n-1) {
            printf("%lld\n", -p.fst);
            return 0;
        }
        for(int e: adj[p.snd]) {
            int v = ab[e] ^ p.snd;
            if (seen[v]) continue;
            ll md = -p.fst % ll(x[e] + y[e]);
            if (md < x[e]) pq.push(pii(p.fst, v));
            else pq.push(pii(p.fst - ll(x[e] + y[e] - md), v));
        }
    }
}