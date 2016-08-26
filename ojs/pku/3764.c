#include <stdio.h>
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
int max(int a, int b) {
	if(a > b) return a;
	return b;
}

int es[100009], nx[200009], ew[200009], to[200009];
int xr[100009];
void dfs(int u, int p, int w) {
	int i;
	xr[u] = w;
	for(i = es[u]; i != -1; i = nx[i])
		if(p != to[i])
			dfs(to[i], u, w ^ ew[i]);
}

int nn;
struct no {
	int a[2];
} ns[3100009];

void add(int i, int b, int w) {
	int bit = !!(w & (1 << (30 - b)));
	if(b == 31) return;
	if(ns[i].a[bit] == -1) {
		ns[nn].a[0] = ns[nn].a[1] = -1;
		ns[i].a[bit] = nn++;
	}
	add(ns[i].a[bit], b + 1, w);
}

int max_xor(int i, int b, int w, int num) {
	int bit = !!(w & (1 << (30-b)));	
	if(b == 31) return w ^ num;
	if(ns[i].a[!bit] == -1) return max_xor(ns[i].a[bit], b + 1, w, (num << 1) + bit);
	return max_xor(ns[i].a[!bit], b + 1, w, (num << 1) + !bit);
}

int main() {
	int mx, i, n, a, b, w;
	while(scanf("%d", &n) != EOF) {
		for(i = 0; i < n; i++) es[i] = -1;
		ns[0].a[0] = ns[0].a[1] = -1; nn = 1;
		for(i = 0; i < n - 1; i++) {
			scanf("%d %d %d", &a, &b, &w);
			nx[2*i] = es[a];
			es[a] = 2*i;
			ew[2*i] = w;
			to[2*i] = b;
			nx[2*i+1] = es[b];
			es[b] = 2*i+1;
			ew[2*i+1] = w;
			to[2*i+1] = a;
		}
		dfs(0, 0, 0);
		for(i = 0; i < n; i++)
			add(0, 0, xr[i]);
		mx = 0;
		for(i = 0; i < n; i++)
			mx = max(mx, max_xor(0, 0, xr[i], 0));
		printf("%d\n", mx);
	}
	return 0;
}
