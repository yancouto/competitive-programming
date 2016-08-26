#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef unsigned long long ull;
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
template<typename T> inline T abs(T t) { return t < 0? -t : t; }
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }
const int N = 31234;

vector<int> c[12];
vector<pii> adj[N];
vector<int> B[N], it[N];
int r[N], dist[N], seen[N];
int S[N], sz[N];

int find(int i) {
	if(S[S[i]] != S[i]) S[i] = find(S[i]);
	return S[i];
}

void join(int a, int b) {
	if((a = find(a)) == (b = find(b))) return;
	if(sz[a] < sz[b]) swap(a, b);
	S[b] = a;
	sz[a] += sz[b];
	for(int x : it[b]) it[a].pb(x);
}

int main() {
	int i, n, m, a, b, t, j;
	scanf("%d %d", &n, &m);
	for(i = 0; i < n; i++) {
		scanf("%d", &r[i]); B[i].clear();
		c[r[i]].pb(i);
	}
	for(i = 0; i < m; i++) {
		scanf("%d %d %d", &a, &b, &t); a--; b--;
		adj[a].pb(pii(b, t));
		adj[b].pb(pii(a, t));
	}
	for(j = 10; j > 0; j--) {
		for(i = 0; i < n; i++) seen[i] = 0, dist[i] = INT_MAX;
		priority_queue<pii> pq;
		for(i = j + 1; i <= 10; i++)
			for(int x : c[i])
				pq.push(pii(0, x));
		while(!pq.empty()) {
			pii a = pq.top(); pq.pop();
			if(seen[a.snd]) continue;
			printf("at %d with %d\n", a.snd+1, -a.fst);
			seen[a.snd] = 1;
			dist[a.snd] = -a.fst;
			for(pii e : adj[a.snd])
				pq.push(pii(a.fst - e.snd, e.fst));
		}
		for(i = 0; i < n; i++) {
			seen[i] = 0, S[i] = i, sz[i] = 1;
			it[i].clear(); it[i].pb(i);
		}
		for(int x : c[j])
			pq.push(pii(0, x));
		while(!pq.empty()) {
			pii a = pq.top(); pq.pop();
			if(seen[a.snd]) continue;
			seen[a.snd] = 1;
			for(pii e : adj[a.snd]) {
				if(dist[e.fst] <= -a.fst + e.snd) continue;
				join(a.snd, e.fst);
				if(!seen[e.fst]) pq.push(pii(a.fst - e.snd, e.fst));
			}
		}
		for(i = 0; i < n; i++)
			if(r[i] == j)
				for(int x : it[find(i)]) {
					printf("add %d to %d\n", i+1, x+1);
					B[x].pb(i);
				}
	}
	int tot = 0;
	for(i = 0; i < n; i++)
		tot += B[i].size();
	printf("%d\n", tot);
}
