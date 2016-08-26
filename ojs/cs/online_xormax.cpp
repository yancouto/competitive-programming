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
const int N = 112345;
int tr[2123456 * 32][2], a[N], all[N], d[N], o[N], ans[N], r[N], sz[N], p[N];
//int st[M], sn = 0;

void clear(int u) {
	return;
	//st[sn++] = u;
	if(tr[u][0]) clear(tr[u][0]);
	if(tr[u][1]) clear(tr[u][1]);
	tr[u][0] = tr[u][1] = 0;
}

int n, en = 1, mx;
int node() {
	//if(sn) return st[--sn];
	return en++;
}

void check(int v, int x) {
	int m = 0;
	for(int i = 29; i >= 0; i--) {
		int b = ((x >> i) & 1);
		if(tr[v][!b]) {
			v = tr[v][!b];
			m |= (1 << i);
		} else v = tr[v][b];
	}
	mx = max(mx, m);
}

void add(int l, int id, bool al=true) {
	o[id] = l;
	sz[l]++;
	all[l] ^= a[id];
	int x = (al? all[l] : a[id])  ^ d[l];
	int v = r[l];
	for(int i = 29; i >= 0; i--) {
		int &nx = tr[v][(x >> i) & 1];
		if(!nx) nx = node();
		v = nx;
	}
	check(r[l], x);
	check(r[l], d[l]);
}

void join(int l, int r) {
	if(sz[o[l]] > sz[o[r]]) {
		clear(::r[r]);
		int bk = o[r];
		for(int i = r; i <= n && o[i] == bk; i++)
			add(o[l], i);
	} else {
		clear(::r[l]);
		int bk = o[l];
		for(int i = l; i >= 1 && o[i] == bk; i--) {
			d[o[r]] ^= a[i];
			add(o[r], i, false);
		}
	}
}

int main(int argn, char **args) {
	int i;
	scanf("%d", &n);

	for(i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	for(i = 1; i <= n; i++)
		scanf("%d", &p[n - i + 1]);
	for(int j = 1; j <= n; j++) {
		i = p[j];
		r[i] = node();
		o[i] = i;
		add(i, i);
		if(o[i - 1]) join(i - 1, i);
		if(o[i + 1]) join(i, i + 1);
		ans[n - j + 1] = mx;
	}
	for(i = 1; i <= n; i++)
		printf("%d\n", ans[i]);
}
