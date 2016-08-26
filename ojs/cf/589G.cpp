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
const int MAX = 200009;
int t[MAX], d[MAX], r[MAX], b[MAX];

ll tr[MAX << 2]; int lazy[MAX << 2]; int ze[MAX << 2];
inline int L(int i) { return i << 1; }
inline int R(int i) { return (i << 1) + 1; }

void build(int i, int le, int ri) {
	if(le == ri) { tr[i] = t[le]; return; }
	int mi = (le + ri) / 2;
	build(L(i), le, mi);
	build(R(i), mi + 1, ri);
	tr[i] = tr[L(i)] + tr[R(i)];
}

void unlaze(int i, int le, int ri) {
	if(lazy[i] == 0) return;
	tr[i] += ll(ri - le + 1 - ze[i]) * lazy[i];
	if(le != ri) lazy[L(i)] += lazy[i], lazy[R(i)] += lazy[i];
	lazy[i] = 0;
}

void set0(int i, int le, int ri, int x) {
	unlaze(i, le, ri);
	if(le == ri) { ze[i] = 1; tr[i] = 0; return; }
	int mi = (le + ri) / 2;
	if(x <= mi) set0(L(i), le, mi, x);
	else set0(R(i), mi + 1, ri, x);
	unlaze(L(i), le, mi);
	unlaze(R(i), mi + 1, ri);
	ze[i] = ze[L(i)] + ze[R(i)];
	tr[i] = tr[L(i)] + tr[R(i)];
}

ll get(int i, int le, int ri, int ql, int qr) {
	unlaze(i, le, ri);
	if(le > qr || ri < ql) return 0;
	if(le >= ql && ri <= qr) return tr[i];
	int mi = (le + ri) / 2;
	return get(L(i), le, mi, ql, qr) + get(R(i), mi + 1, ri, ql, qr);
}
int p[MAX], p2[MAX];
int main() {
	int n, m, i;
	scanf("%d %d", &n, &m);
	for(i = 0; i < m; i++) {
		scanf("%d", &t[i]);
		//t[i] = (rand() % 10) + 1;
		//printf("%d ", t[i]);
		p2[i] = i;
	}
	//putchar('\n');
	sort(p2, p2 + m, [](int i, int j) { return t[i] < t[j]; });
	build(1, 0, m - 1);
	for(i = 0; i < n; i++) {
		scanf("%d %d", &d[i], &r[i]);
		//d[i] = rand() % 12;
		//r[i] = (rand() % (m*7)) + 1;
		//printf("%d %d\n", d[i], r[i]);
		p[i] = i;
	}
	sort(p, p + n, [](int i, int j) { return d[i] < d[j]; }); 
	int cur = 0;
	for(i = 0; i < n; i++) {
		int j = p[i];
		//printf("it %d | %d\n", i, j);
		while(cur < m && t[p2[cur]] <= d[j]) {
			//printf("zero %d\n", p2[cur]);
			set0(1, 0, m - 1, p2[cur++]);
		}
		int k = d[j];
		if(i > 0) k -= d[p[i - 1]];
		lazy[1] = -k;
		unlaze(1, 0, m - 1);
		if(tr[1] < r[j]) { b[j] = 0; continue; }
		int le = 1, ri = m;
		while(le < ri) {
			int mi = (le + ri) / 2;
			if(get(1, 0, m - 1, 0, mi - 1) >= r[j]) ri = mi;
			else le = mi + 1;
		}
		b[j] = le;
	}
	//for(i = 0; i < n; i++) {
	//	int tot = 0;
	//	int j;
	//	for(j = 0; j < m && tot < r[i]; j++)
	//		tot += max(0, t[j] - d[i]);
	//	if(tot < r[i]) printf("%d - %d\n", 0, b[i]);
	//	else printf("%d - %d\n", j, b[i]);
	//	if(tot < r[i]) assert(b[i] == 0);
	//	else assert(b[i] == j);
	//}
	for(i = 0; i < n; i++)
		printf("%d ", b[i]);
	putchar('\n');
}
