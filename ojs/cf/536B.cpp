#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef pair<int, int> pii;
typedef unsigned long long ull;
typedef long long ll;
typedef long double ld;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
template<typename T> inline T abs(T t) { return t < 0? -t : t; }
const ull modn = 1000000007;
inline ull mod(ull x) { return x % modn; }

const int MAX = 1000009;
ull hs[MAX], pt[MAX];
char str[MAX];

bool eq(int i, int j, int x, int y) {
	if(i > x) { swap(i, x); swap(j, y); }
	//printf("%d %d %d %d\n", i, j, x, y);
	ull h1 = mod(hs[j] - hs[i-1] + modn); ull h2 = mod(hs[y] - hs[x-1] + modn);
	h1 = mod(h1 * pt[x - i]);
	//if(h1 != h2) printf("bad match %I64u %I64u\n", h1, h2);
	return h1 == h2;
}

bool ok;
inline int l(int i) { return i << 1; }
inline int r(int i) { return l(i) + 1; } 
int lzl[MAX << 2], lzr[MAX << 2];
int ct;
void unlaze(int i, int from, int to) {
	if(lzl[i] == -1) return;
	//printf("unlazing (%d, %d)\n", from, to);
	if(from != to) {
		int mid = (from + to) / 2;
		int p = l(i);
		if(lzl[p] != -1 && !eq(lzl[i], lzl[i] + mid - from, lzl[p], lzr[p]))
			ok = false;
		lzl[p] = lzl[i];
		lzr[p] = lzl[i] + (mid - from);
		p = r(i);
		if(lzl[p] != -1 && !eq(lzl[i] + mid - from + 1, lzr[i], lzl[p], lzr[p]))
			ok = false;
		lzl[p] = lzl[i] + (mid - from + 1);
		lzr[p] = lzr[i];
	} else ct++;
}

void set_tree(int i, int from, int to, int ql, int qr) {
	unlaze(i, from, to);
	if(from > qr || to < ql) return;
	if(from >= ql && to <= qr) {
		lzl[i] = from - ql;
		lzr[i] = to - ql;
		//printf("set %d (%d, %d)\n", i, from, to);
		unlaze(i, from, to);
		return;
	}
	int mid = (from + to) / 2;
	set_tree(l(i), from, mid, ql, qr);
	set_tree(r(i), mid + 1, to, ql, qr);
}

void flushh(int i, int from, int to) {
	//printf("here (%d, %d)\n", from, to);
	unlaze(i, from, to);
	if(from == to) return;
	int mid = (from + to) / 2;
	flushh(l(i), from, mid);
	flushh(r(i), mid + 1, to);
}

int main() {
	int i, j, x, n, m;
	ok = true;
	memset(lzl, -1, sizeof lzl);
	memset(lzr, -1, sizeof lzr);
	scanf("%d %d", &n, &m);
	scanf(" %s", str);
	ull h = 0, pot = 1;
	for(i = 0; str[i]; i++) {
		h = mod(h + str[i] * pot);
		hs[i] = h; pt[i] = pot;
		pot = mod(pot * 267);
	}
	pt[i] = pot;
	int sz = strlen(str);
	for(i = 0; i < m; i++) {
		scanf("%d", &x);
		//printf("set (%d, %d)\n", x - 1, x - 1 + sz - 1);
		set_tree(1, 0, n - 1, x - 1, x - 1 + sz - 1);
		//puts("-------");
	}
	ct = 0;
	flushh(1, 0, n - 1);
	pot = 1; ct = n - ct;
	for(i = 0; i < ct; i++) pot = mod(pot * 26);
	if(!ok) puts("0");
	else printf("%I64u\n", pot);
	return 0;
}
