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
const int MAX = 100003;
int t[MAX * 27], tn, L[MAX * 27], R[MAX * 27];
int build(int le, int ri) {
	int id = tn++;
	if(le == ri) return id;
	int mi = (le + ri) / 2;
	L[id] = build(le, mi);
	R[id] = build(mi + 1, ri);
	return id;
}

int update(int oid, int le, int ri, int x) {
	int id = tn++;
	t[id] = t[oid] + 1;
	if(le == ri) return id;
	int mi = (le + ri) / 2;
	L[id] = L[oid]; R[id] = R[oid];
	if(x <= mi) L[id] = update(L[oid], le, mi, x);
	else R[id] = update(R[oid], mi + 1, ri, x);
	return id;
}


int w[MAX], p[MAX], inv[MAX], n, lc[MAX][18], root[MAX], nv[MAX];
int to[MAX<<1], nx[MAX<<1], head[MAX], en;
void dfs(int u, int p, int nv) {
	::nv[u] = nv;
	lc[u][0] = p;
	for(int i = 1; i < 18; i++)
		lc[u][i] = lc[lc[u][i-1]][i-1];
	root[u] = update(root[p], 0, n - 1, inv[u]);	
	for(int i = head[u]; i != -1; i = nx[i])
		if(to[i] != p)
			dfs(to[i], u, nv + 1);
}

int lca(int u, int v) {
	if(nv[u] > nv[v]) swap(u, v);
	if(nv[u] < nv[v])
		for(int k = 17; k >= 0; k--)
			if(nv[lc[v][k]] >= nv[u])
				v = lc[v][k];
	if(u == v) return u;
	for(int k = 17; k >= 0; k--)
		if(lc[u][k] != lc[v][k])
			u = lc[u][k], v = lc[v][k];
	return lc[u][0];
}

bool cmp(int i, int j) { return w[i] < w[j]; }

int main() {
	int i, m, a, b, c;
	scanf("%d %d", &n, &m);
	for(i = 0; i < n; i++) {
		scanf("%d", &w[i]);
		p[i] = i;
		head[i] = -1;
	}
	sort(p, p + n, &cmp);
	for(i = 0; i < n; i++)
		inv[p[i]] = i;
	build(0, n - 1);
	for(i = 0; i < n - 1; i++) {
		scanf("%d %d", &a, &b); a--; b--;
		to[en] = b; nx[en] = head[a]; head[a] = en++;
		to[en] = a; nx[en] = head[b]; head[b] = en++;
	}
	dfs(0, 0, 0);
	for(i = 0; i < m; i++) {
		scanf("%d %d %d", &a, &b, &c); a--; b--;
		int d = lca(a, b);
		int l = 0, r = n - 1;
		a = root[a]; b = root[b]; int la = root[d], lp = d? root[lc[d][0]] : 0;
		while(l != r) {
			int q = t[L[a]] + t[L[b]] - t[L[la]] - t[L[lp]];
			int mi = (l + r) / 2;
			if(q >= c) { r = mi; a = L[a]; b = L[b]; la = L[la]; lp = L[lp]; }
			else { l = mi + 1; c -= q; a = R[a]; b = R[b]; la = R[la]; lp = R[lp]; }
		}
		printf("%d\n", w[p[l]]);
	}
}
