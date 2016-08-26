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

const int N = 90009;
enum typ {ADD, COMP, REM};

int S[N], sz[N], st[N], sn, comp;
int a[N], b[N], ea[N], er[N], p[N], c[N];
int qt[N], qe[N], qa[N], qn;

int find(int i) {
	while(S[i] != i) i = S[i];
	return i;
}

void join(int a, int b) {
	if((a = find(a)) == (b = find(b))) return;
	comp--;
	if(sz[a] < sz[b]) swap(a, b);
	S[b] = a;
	sz[a] += sz[b];
	st[sn++] = b;
}

void query(int t, int e=0) {
	qt[qn] = t; qe[qn++] = e;
}

void rollback() {
	sn--;
	sz[S[st[sn]]] -= sz[st[sn]];
	S[st[sn]] = st[sn];
	comp++;
}

void process(int l, int r) {
	if(l == r) return (void) (qa[l] = comp);
	int P = sn, m = (l + r) / 2, i;
	for(i = l; i <= m; i++)
		if(qt[i] == ADD && er[qe[i]] > r)
			join(a[qe[i]], b[qe[i]]);
	process(m + 1, r);
	while(sn != P) rollback();
	for(i = m + 1; i <= r; i++)
		if(qt[i] == REM && ea[qe[i]] < l)
			join(a[qe[i]], b[qe[i]]);
	process(l, m);
	while(sn != P) rollback();
}

int m;
int start;
bool pos(int k) {
	int i, j = 0; qn = 0;
	for(i = 0; i < m; i++) {
		for(; j < m && c[p[j]] - c[p[i]] <= k; j++) ea[p[j]] = qn, query(ADD, p[j]);
		query(COMP);
		er[p[i]] = qn; query(REM, p[i]);
	}
	process(0, qn - 1);
	for(i = 0; i < qn; i++)
		if(qt[i] == COMP && qa[i] == 1)
			return start = qe[i + 1], true;
	return false;
}

int main() {
	int i, n;
	scanf("%d %d", &n, &m);
	for(i = 0; i < n; i++) S[i] = i, sz[i] = 1;
	for(i = 0; i < m; i++)
		scanf("%d %d %d", &a[i], &b[i], &c[i]), p[i] = i, a[i]--, b[i]--;
	stable_sort(p, p + m, [](int i, int j) { return c[i] < c[j]; });
	comp = n;
	int l = 0, r = 1000000003;
	while(l < r) {
		int k = (l + r) / 2;
		if(pos(k)) r = k;
		else l = k + 1;
	}
	pos(l);
	for(i = 0; p[i] != start; i++);
	for(; i < m && comp > 1; i++) {
		if(find(a[p[i]]) != find(b[p[i]])) {
			printf("%d ", p[i] + 1);
			join(a[p[i]], b[p[i]]);
		}
	}
	putchar('\n');
}
