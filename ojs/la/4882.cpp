#include <bits/stdc++.h>
using namespace std;

int bad[1009];
int S[1009], sz[1009];
int find(int i) {
	if(S[S[i]] != S[i]) S[i] = find(S[i]);
	return S[i];
}

void join(int a, int b) {
	a = find(a); b = find(b);
	if(a == b) return;
	if(sz[a] < sz[b]) swap(a, b);
	sz[a] += sz[b];
	S[b] = a;
}

struct edge {
	int u, v, c;
	void read() { scanf("%d %d %d", &u, &v, &c); u--; v--; }
	bool operator < (edge o) const { return c < o.c; }
} es[100009];

int main() {
	int i, n, m, p, x;
	while(scanf("%d %d %d", &n, &m, &p) != EOF) {
		for(i = 0; i < n; i++) {
			bad[i] = 0;
			S[i] = i; sz[i] = 1;
		}
		for(i = 0; i < p; i++) {
			scanf("%d", &x);
			bad[--x] = 1;
		}
		for(i = 0; i < m; i++)
			es[i].read();
		sort(es, es + m);
		int tot = 0;
		for(i = 0; i < m; i++) {
			if(bad[es[i].u] || bad[es[i].v]) continue;
			if(find(es[i].u) == find(es[i].v)) continue;
			tot += es[i].c;
			join(es[i].u, es[i].v);
		}
		int w = 0;
		for(i = 0; i < n; i++)
			w += !bad[i];
		for(i = 0; i < n && bad[i]; i++);
		if(i < n && sz[find(i)] != w) { puts("impossible"); continue; }
		for(i = 0; i < m; i++) {
			if(n > 2 && (bad[es[i].u] == bad[es[i].v])) continue;
			if(find(es[i].u) == find(es[i].v)) continue;
			tot += es[i].c;
			join(es[i].u, es[i].v);
		}
		if(sz[find(0)] != n) { puts("impossible"); continue; }
		printf("%d\n", tot);
	}
}
