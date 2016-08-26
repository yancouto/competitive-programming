#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef pair<int, int> pii;
typedef unsigned long long ull;
typedef long long ll;
typedef long double ld;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
template<typename T> inline T abs(T t) { return t < 0? -t : t; }
const ull modn = 1000000007;
inline ull mod(ull x) { return x % modn; }

struct no {
	int c;
	ll d;
	bool up;
	bool operator < (no o) const { return d > o.d; }
};

int seen[100009][2];
vector<int> adj[100009];
int n;
int h[100009], c[100009];

ll solve() {
	priority_queue<no> pq;
	pq.push({0, c[0], true});
	pq.push({0, c[0], false});
	while(!pq.empty()) {
		no x = pq.top(); pq.pop();
		if(x.c == n - 1) return x.d;
		if(seen[x.c][x.up]) continue;
		seen[x.c][x.up] = 1;
		for(int v : adj[x.c]) {
			if(h[v] >= h[x.c]) pq.push({v, x.d + (!x.up) * c[x.c], true});
			if(h[v] <= h[x.c]) pq.push({v, x.d + x.up * c[x.c], false});
		}
	}
	return -1;
}

int main() {
	int i, m, a, b;
	scanf("%d %d", &n, &m);
	for(i = 0; i < n; i++)
		scanf("%d", &h[i]);
	for(i = 0; i < n; i++)
		scanf("%d", &c[i]);
	for(i = 0; i < m; i++) {
		scanf("%d %d", &a, &b);
		adj[--a].pb(--b);
		adj[b].pb(a);
	}
	printf("%lld\n", solve());
}
