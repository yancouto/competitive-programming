#include <bits/stdc++.h>
using namespace std;
#define dst first
#define i second
typedef unsigned long long ull;
typedef long long ll;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
template<typename T> inline T abs(T t) { return t < 0? -t : t; }
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }
const int N = 20009;

struct fraq {
	ll p, q; // p / q
	bool operator < (fraq o) const { 
		return p * o.q < q * o.p;
	}
	fraq mn(fraq o) {
		return min(*this, o);
	}
};
typedef pair<fraq, int> no;

fraq cp[N], dist[N];
int nx[N], he[N], mrk[N], seen[N], p[N], to[N], en;

int n;
fraq solve() {
	int i;
	for(i = 0; i < n; i++) seen[i] = 0, mrk[i] = 0;
	priority_queue<no> pq;
	pq.push(no({1, 0}, 0));
	while(!pq.empty()) {
		no x = pq.top(); pq.pop();
		if(seen[x.i]) continue;
		if(x.i == n - 1) break;
		seen[x.i] = true;
		for(int e = he[x.i]; e != -1; e = nx[e]) {
			if(cp[e].p == 0) continue;
			if(!mrk[to[e]] || dist[to[e]] < x.dst.mn(cp[e])) {
				dist[to[e]] = x.dst.mn(cp[e]);
				pq.push(no(x.dst.mn(cp[e]), to[e]));
				p[to[e]] = e;
				mrk[to[e]] = true;
			}
		}
	}
	int u = n - 1;
	while(u != 0) {
		if(p[u] & 1) { // inv
			cp[p[u] ^ 1].q--;
			cp[p[u]].q--;
			if(cp[p[u]].q == 0) cp[p[u]] = fraq{0, 1};
		} else {
			cp[p[u] ^ 1] = cp[p[u]];
			cp[p[u]].q++;
		}
		u = to[p[u] ^ 1];
	}
	return dist[n - 1];
}

int main() {
	int i, m, x, a, b, c;
	scanf("%d %d %d", &n, &m, &x);
	for(i = 0; i < n; i++) he[i] = -1;
	for(i = 0; i < m; i++) {
		scanf("%d %d %d", &a, &b, &c); a--; b--;
		cp[en] = fraq{c, 1}; to[en] = b; nx[en] = he[a]; he[a] = en++;
		cp[en] = fraq{0, 1}; to[en] = a; nx[en] = he[b]; he[b] = en++;
	}
	fraq A;
	for(int i = 0; i < x; i++)
		A = solve();
	printf("%.10f\n", double(A.p * ll(x)) / A.q);
}
