#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAX = 1000009, MAXV = 2009;
int val[MAX], nx[MAX], head[MAXV], en;
int lh[MAXV], nu[MAX], ln, d[MAXV], f[MAXV], tempo;

inline bool is_anc(int anc, int v) {
	return d[v] >= d[anc] && f[v] <= f[anc];
}

inline bool on_cyc(int e, int f) {
	return is_anc(val[f], val[e ^ 1]) && is_anc(val[e], val[f]) && is_anc(val[f ^ 1], val[e ^ 1]) && is_anc(val[e], val[f ^ 1]);
}

void process(int e) {
	if(d[val[e]] > d[val[e ^ 1]]) return;
	int x = ln;
	for(int i = 0; i < x; i++) {
		int on = -1, off = -1;
		while(lh[i] != -1) {
			int k = lh[i];
			lh[i] = nx[lh[i]];
			if(on_cyc(e, val[k])) {
				nu[val[k]]++;
				nx[k] = on; on = k;
			} else {
				nx[k] = off; off = k;
			}
		}
		if(i == 0) { lh[i] = off; if(on != -1) lh[ln++] = on; continue; }
		if(on > off) swap(on, off);
		lh[i] = off;
		if(on != -1) lh[ln++] = on;
	}
	x = 1;
	for(int i = 1; i < ln; i++)
		if(nx[lh[i]] != -1 || nu[val[lh[i]]] <= 1)
			lh[x++] = lh[i];
	ln = x;
}

void dfs(int u, int pe) {
	d[u] = tempo++;
	for(int e = head[u]; e != -1; e = nx[e]) {
		if((e ^ 1) == pe) continue;
		if(d[val[e]]) process(e);
		else {
			val[en] = e; nx[en] = lh[0]; lh[0] = en++;
			dfs(val[e], e);
		}
	}
	f[u] = tempo++;
}

int main() {
	int i, n, m, a, b, j;
	scanf("%d %d", &n, &m);
	if(n == 2) { puts("0"); return 0; }
	for(i = 0; i < n; i++)
		head[i] = lh[i] = -1;
	tempo = 1;
	for(i = 0; i < m; i++) {
		scanf("%d %d", &a, &b); a--; b--;
		val[en] = b; nx[en] = head[a]; head[a] = en++;
		val[en] = a; nx[en] = head[b]; head[b] = en++;
	}
	ln = 1;
	dfs(0, -1);
	ll tot = 0;
	ll sz = 0;
	for(i = lh[0]; i != -1; i = nx[i]) sz++;
	tot += sz * ll(m - 1) - sz * (sz - 1) / 2;
	for(i = 1; i < ln; i++) {
		sz = 0;
		for(j = lh[i]; j != -1; j = nx[j]) sz++;
		if(sz && nu[val[lh[i]]] == 1) sz++;
		tot += sz * (sz - 1) / 2;
	}
	printf("%lld\n", tot);
}
