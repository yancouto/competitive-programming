#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back

const int N = 1e7+2;
const int T = 4.6e6;

int n, m;
int a[N], b[N], p[N]; ll w[N];
vector<int> adj[N];
int uf[N];
unsigned s;
unsigned r[((N+31)/32) + 2];
int ar[N];
int need;

inline unsigned getNext () {
	s ^= (s<<13);
	s ^= (s>>17);
	s ^= (s<<5);
	return s;
}

inline int find (int u) {
	if (uf[u] < 0) return u;
	return uf[u] = find(uf[u]);
}

inline bool join (int u, int v) {
	if ((u = find(u)) == (v = find(v))) { ar[u]++; return 0; }
	if (uf[u] > uf[v]) swap(u,v);
	uf[u] += uf[v];
	uf[v] = u;
	ar[u] += ar[v];
	ar[u]++;
	return 1;
}

inline void mst (int * v, int s) {
	sort(v, v+s, [] (int i, int j) { return w[i] < w[j]; });
	for (int _i = 0; need && _i < s; _i++) {
		int i = v[_i];
		if (join(a[i],b[i])) { need--; r[i/32] |= (1<<(i%32)); }
	}
}

int q[N];
int select (int * v, int f, int t) {
	int p = rand()%f;
	int a = 0, b = f-1;
	for (int i = 0; i < f; i++) { if (w[v[i]] <= w[v[p]]) q[a++] = v[i]; else q[b--] = v[i]; }
	for (int i = 0; i < f; i++) v[i] = q[i];
	if (a >= t) return a;
	else return a + select(v+a, f-a, t-a);
}

inline void prn(int x) {
	int y = 0, sz = 0;
	for(; x; x /= 10, sz++)
		y = (y << 3) + (y << 1) + (x % 10);
	for(; sz--; y /= 10) putchar_unlocked('0' + (y % 10));
	putchar_unlocked('\n');
}

int main () {
	scanf("%d %d %u", &n, &m, &s);
	for (int i = 0; i < n; i++) uf[i] = -1;
	need = n;
	for (int i = 0; i < m; i++) {
		a[i] = getNext()%n;
		b[i] = getNext()%n;
		join(a[i],b[i]);
		w[i] = getNext()/4;
		w[i] = w[i] * getNext();
	}

	int ps = 0;
	for (int i = 0; i < m; i++)
		adj[find(a[i])].pb(i);

	for (int i = 0; i < n; i++) { need -= (uf[i] < 0); uf[i] = -1; }
	need = (need+1)/2;

	for (int i = 0; i < n; i++) {
		if (adj[i].empty()) continue;
		int s = adj[i].size();
		if (s > T) { s = T; nth_element(adj[i].begin(), adj[i].begin() + T, adj[i].end()); }
		mst(&adj[i][0], s);
	}

	for (int i = 0; i <= (m-1)/32; i++) prn(r[i]);
}
