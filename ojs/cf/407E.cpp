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

struct kd {
	int mn, mx, sz;
	int val() const { return (mx - mn - sz + 1); }
	bool operator < (const kd &o) const { return val() < o.val(); }
	void deb() {
		printf("{%d, %d, %d}->%d\n", mn, mx, sz, val());
	}
};
struct kk {
	kd a, mn, mx;
};
kd join(kd a, kd b) {
	return min(a, b);
}
kk join(kk a, kk b) {
	return {min(a.a, b.a), min(a.mn, b.mn), min(a.mx, b.mx)};
}
const int MAX = 200009;
kk tree[MAX << 2];
inline int l(int i) { return i << 1; }
inline int r(int i) { return (i << 1) + 1; }
int lsz[MAX << 2], lmn[MAX << 2], lmx[MAX << 2];

void build_tree(int i, int from, int to) {
	lsz[i] = lmn[i] = lmx[i] = -1;
	if(from == to) {
		kd c = {0, 0, 0};
		tree[i] = {c, c, c};
		return;
	}
	int mid = (from + to) / 2;
	build_tree(l(i), from, mid);
	build_tree(r(i), mid + 1, to);
	tree[i] = join(tree[l(i)], tree[r(i)]);
}

void unsz(int i, int from, int to) {
	if(lsz[i] == -1) return;
	tree[i].a.sz += lsz[i];
	tree[i].mn.sz += lsz[i];
	tree[i].mx.sz += lsz[i];
	if(from != to) {
		lsz[l(i)] += lsz[i];
		lsz[r(i)] += lsz[i];
	}
	lsz[i] = -1;
}

void unmn(int i, int from, int to) {
	if(lmn[i] == -1) return;
	//printf("unmn(%d, %d, %d) -- before\n", i, from, to);
	//tree[i].a.deb();
	tree[i].a = tree[i].mx;
	tree[i].a.mn = lmn[i];
	tree[i].mn.mn = lmn[i];
	//tree[i].a.deb();
	if(from != to) {
		lmn[l(i)] = lmn[i];
		lmn[r(i)] = lmn[i];
	}
	lmn[i] = -1;
}
void unmx(int i, int from, int to) {
	if(lmx[i] == -1) return;
	//printf("unmx(%d, %d, %d) -- before\n", i, from, to);
	//tree[i].a.deb();
	tree[i].a = tree[i].mn;
	tree[i].a.mx = lmx[i];
	tree[i].mx.mx = lmx[i];
	//tree[i].a.deb();
	if(from != to) {
		lmx[l(i)] = lmx[i];
		lmx[r(i)] = lmx[i];
	}
	lmx[i] = -1;
}
inline void unlaze(int i, int f, int t) { unsz(i, f, t); unmn(i, f, t); unmx(i, f, t); }

kd query_tree(int i, int from, int to, int ql, int qr) {
	unlaze(i, from, to);
	if(from > qr || to < ql) return {0, INT_MAX - 10, 0};
	if(from >= ql && to <= qr) return tree[i].a;
	int mid = (from + to) / 2;
	return join(query_tree(l(i), from, mid, ql, qr),
	          query_tree(r(i), mid + 1, to, ql, qr));
}
void add_sz(int i, int from, int to, int ql, int qr) {
	unlaze(i, from, to);
	if(from > qr || to < ql) return;
	if(from >= ql && to <= qr) {
		printf("doing sz(%d, %d) -- ", from + 1, to + 1); tree[i].a.deb();
		lsz[i] = 1;
		unsz(i, from, to);
		tree[i].a.deb();
		return;
	}
	int mid = (from + to) / 2;
	add_sz(l(i), from, mid, ql, qr);
	add_sz(r(i), mid + 1, to, ql, qr);
	tree[i] = join(tree[l(i)], tree[r(i)]);
}
void set_mn(int i, int from, int to, int ql, int qr, int x) {
	unlaze(i, from, to);
	if(from > qr || to < ql) return;
	if(from >= ql && to <= qr) {
		lmn[i] = x;
		unmn(i, from, to);
		return;
	}
	int mid = (from + to) / 2;
	set_mn(l(i), from, mid, ql, qr, x);
	set_mn(r(i), mid + 1, to, ql, qr, x);
	tree[i] = join(tree[l(i)], tree[r(i)]);
}
void set_mx(int i, int from, int to, int ql, int qr, int x) {
	unlaze(i, from, to);
	if(from > qr || to < ql) return;
	if(from >= ql && to <= qr) {
		lmx[i] = x;
		unmx(i, from, to);
		return;
	}
	int mid = (from + to) / 2;
	set_mx(l(i), from, mid, ql, qr, x);
	set_mx(r(i), mid + 1, to, ql, qr, x);
	tree[i] = join(tree[l(i)], tree[r(i)]);
}
void set_mnmx(int i, int from, int to, int qi, int x) {
	unlaze(i, from, to);
	if(from == to) {
		tree[i].a.mn = tree[i].a.mx = tree[i].mn.mn = tree[i].mx.mx = x;
		return;
	}
	int mid = (from + to) / 2;
	if(qi <= mid) set_mnmx(l(i), from, mid, qi, x);
	else set_mnmx(r(i), mid + 1, to, qi, x);
	tree[i] = join(tree[l(i)], tree[r(i)]);
}

map<int, int> ocs, noc;
int a[MAX], n;
void norm(int &s, int e) {
	noc[ocs[a[e]]]--;
	noc[++ocs[a[e]]]++;
	while(noc.rbegin()->fst > 1) {
		if(--noc[ocs[a[s]]] == 0) noc.erase(ocs[a[s]]);
		noc[--ocs[a[s++]]]++;
	}
}
int mn[MAX][20], mx[MAX][20]; 
inline int get_mn(int s, int e) {
	int k = 31 - __builtin_clz(e - s + 1);
	return min(mn[s][k], mn[e - (1 << k) + 1][k]);
}
inline int get_mx(int s, int e) {
	int k = 31 - __builtin_clz(e - s + 1);
	return max(mx[s][k], mx[e - (1 << k) + 1][k]);
}

void pre() {
	int i, j;
	for(i = 0; i < n; i++)
		mn[i][0] = mx[i][0] = a[i];
	for(j = 1; j < 20; j++)
		for(i = 0; i < n; i++) {
			if(i + (1 << j) - 1 >= n) {
				mn[i][j] = mn[i][j - 1];
				mx[i][j] = mx[i][j - 1];
				continue;
			}
			mn[i][j] = min(mn[i][j - 1], mn[i + (1 << j) - 1][j - 1]);
			mx[i][j] = max(mx[i][j - 1], mx[i + (1 << j) - 1][j - 1]);
		}
}

int bl, br, k;
void process_mn(int s, int e, int sl, int i) {
	int sr = i;
	while(sl < sr) {
		int mid = (sl + sr) / 2;
		if(get_mn(mid, i) == mn[i][0]) sr = mid;
		else sl = mid + 1;
	}
	if(sl == i) return;
	printf("upd (%d, %d) min %d\n", sl+1, i+1, a[i]);
	set_mn(1, s, e, sl, i, a[i]);
}
void process_mx(int s, int e, int sl, int i) {
	int sr = i;
	while(sl < sr) {
		int mid = (sl + sr) / 2;
		if(get_mx(mid, i) == mx[i][0]) sr = mid;
		else sl = mid + 1;
	}
	if(sr == i) return;
	printf("upd (%d, %d) max %d\n", sl+1, i+1, a[i]);
	set_mx(1, s, e, sl, i, a[i]);
}
void process_kd(int s, int e, int sl, int i, int &ql, int &qr) {
	if(query_tree(1, s, e, sl, i).val() > k) { ql = e + 1; qr = -1; return; }
	puts("SEARCH");
	while(ql < qr) {
		int mid = (ql + qr) / 2;
		printf("(%d, %d, %d) -> ", ql, mid, qr); query_tree(1, s, e, sl, mid).deb();
		if(query_tree(1, s, e, sl, mid).val() <= k) qr = mid;
		else ql = mid + 1;
	}
	printf("(%d, %d) bestOOO\n", ql + 1, i + 1);
}
void deb(int s, int e, int ql, int qr) {
	for(int i = ql; i <= qr; i++) {
		kd a = query_tree(1, s, e, i, i);
		printf("(%d, %d) -- {%d, %d, %d}->%d\n", i + 1, qr + 1, a.mn, a.mx, a.sz, a.val());
	}
}

void solve(int s, int e) {
	printf("solve(%d, %d)\n", s + 1, e + 1);
	ocs.clear(); noc.clear(); noc[0] = 0;
	build_tree(1, s, e);
	int i, sl = s;
	for(i = s; i <= e; i++) {
		puts("---------------------");
		norm(sl, i);
		printf("[%d, %d]\n", sl + 1, i + 1);
		set_mnmx(1, s, e, i, a[i]);
		add_sz(1, s, e, sl, i);
		process_mn(s, e, sl, i);
		process_mx(s, e, sl, i);
		int left = sl, right = i;
		deb(s, e, sl, i);
		process_kd(s, e, sl, i, left, right);
		printf("(%d, %d) best\n", left + 1, i + 1);
		if(i - left > br - bl) { br = i; bl = left; }
	}
}

void do0() {
	int left = 0;
	for(int i = 0; i < n; i++) {
		if(i && a[i] != a[i - 1]) left = i;
		if(i - left > br - bl) { br = i; bl = left; }
	}
	printf("%d %d\n", bl + 1, br + 1);
	exit(0);
}

int main() {
	int i, d;
	scanf("%d %d %d", &n, &k, &d);
	for(i = 0; i < n; i++){
		scanf("%d", &a[i]);
		a[i] += 1000000001;
	}
	pre();
	bl = 0; br = -1;
	if(d == 0) do0();
	int left = 0;
	for(i = 0; i < n; i++) {
		if(i == n - 1 || (a[i + 1] % d) != (a[i] % d)) {
			a[i] /= d;
			solve(left, i);
			left = i + 1;
		} else a[i] /= d;
	}
	printf("%d %d\n", bl + 1, br + 1);
}
