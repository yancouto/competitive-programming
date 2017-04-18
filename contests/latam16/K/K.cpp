#include <bits/stdc++.h>

using namespace std;
typedef pair<int,int> pii;
typedef long long int ll;

const int N = 1123;

int en = 2, he[N], nx[N], to[N], f[N], c[N];
int n;

void add_edge(int a, int b, int c) {
	//printf("(%d, %d) = %d\n", a, b, c);
	to[en] = b; ::c[en] = c; f[en] = 0; nx[en] = he[a]; he[a] = en++;
	to[en] = a; ::c[en] = 0; f[en] = 0; nx[en] = he[b]; he[b] = en++;
}

int seen[N], t;

int dfs(int a, int b, int fl) {
	//printf("dfs(%d, %d, %d)\n", a, b, fl);
	if(a == b) return fl;
	seen[a] = t;
	for(int e = he[a]; e != -1; e = nx[e]) {
		//printf("%d->%d (%d/%d)\n", a, to[e], f[e], c[e]);
		if(seen[to[e]] < t && c[e] - f[e] > 0)
			if(int a = dfs(to[e], b, min(fl, c[e] - f[e]))) {
				f[e] += a;
				f[e ^ 1] -= a;
				return a;
			}
	}
	return 0;
}

int max_flow(int s, int t) {
	int fl = 0; ::t++;
	while(int a = dfs(s, t, INT_MAX))
		fl += a, ::t++;
	return fl;
}

int a[N], b[N];

bool ok(int x) {
	en = 2;
	memset(he, -1, sizeof he);
	int p = 0, i;
	int s = 2 * n + 3, t = 2* n + 4;
	for(i = 0; i < n; i++) {
		if(i == x - 1) continue;
		if(a[i] == x || b[i] == x)
			p++;
		else {
			add_edge(i, a[i] + n, 1);
			add_edge(i, b[i] + n, 1);
			add_edge(s, i, 1);
		}
	}
	if(p == 0) return 0;
	for(i = 1; i <= n; i++)
		if(i != x) {
			int op = p - 1;
			if(i == a[x - 1] || i == b[x - 1]) op--;
			if(op < 0) return 0;
			add_edge(i + n, t, op);
		}
	int m = max_flow(s, t);
	//printf("[%d] p %d (%d/%d)\n", x, p, m, n - p - 1);
	if(m == n - p - 1) {
		//printf("%d ok\n", x);
		return 1;
	} return 0;
}

int main () {
	int i;
	scanf("%d", &n);
	for(i = 0; i < n; i++)
		scanf("%d %d", &a[i], &b[i]);
	int tot = n;
	for(i = 1; i <= n; i++)
		tot -= ok(i);
	printf("%d\n", tot);
}
