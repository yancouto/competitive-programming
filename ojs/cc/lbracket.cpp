#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }

const int N = 812345;
char s[N];
int lz[N], L[N], R[N];

struct obj {
	int sz, sum, mn, tmn, mx, tmx;
	void negate() {
		sum = -sum;
		swap(mn, mx);
		swap(tmn, tmx);
		mn = -mn;
		mx = -mx;
	}
	void debug() { printf("sz %d sum %d mn %d (%d) mx %d (%d)\n", sz, sum, mn, tmn, mx, tmx); }
} tr[N];

obj join(obj a, obj b) {
	obj c = {a.sz + b.sz, a.sum + b.sum, min(a.mn, b.mn + a.sum), 0, max(a.mx, b.mx + a.sum), 0};
	if(c.mn == a.mn) c.tmn = a.tmn;
	if(c.mn == b.mn + a.sum) c.tmn = max(c.tmn, a.sz + b.tmn);
	if(c.mx == a.mx) c.tmx = a.tmx;
	if(c.mx == b.mx + a.sum) c.tmx = max(c.tmx, a.sz + b.tmx);
	return c;
}

void build(int i, int l, int r) {
	L[i] = l; R[i] = r;
	if(l == r) {
		if(s[l] == '(') tr[i] = {1, 1, 0, 0, 1, 1};
		else tr[i] = {1, -1, -1, 1, 0, 0};
		return;
	}
	int m = (l + r) / 2;
	build(2 * i, l, m);
	build(2 * i + 1, m + 1, r);
	tr[i] = join(tr[2 * i], tr[2 * i + 1]);
}

void unlaze(int i, int l, int r) {
	if(!lz[i]) return;
	tr[i].negate();
	if(l != r) lz[2*i] = !lz[2*i], lz[2*i+1] = !lz[2*i+1];
	lz[i] = 0;
}

void upd(int i, int l, int r, int ql, int qr) {
	unlaze(i, l, r);
	if(l > qr || r < ql) return;
	if(l >= ql && r <= qr) {
		lz[i] = 1;
		unlaze(i, l, r);
		return;
	}
	int m = (l + r) / 2;
	upd(2 * i, l, m, ql, qr);
	upd(2 * i + 1, m + 1, r, ql, qr);
	tr[i] = join(tr[2 * i], tr[2 * i + 1]);
}

vector<int> no;
void query(int i, int l, int r, int ql) {
	unlaze(i, l, r);
	if(r < ql) return;
	if(l >= ql) {
		no.pb(i);
		return;
	}
	if(l == r) return;
	int m = (l + r) / 2;
	query(2 * i, l, m, ql);
	query(2 * i + 1, m + 1, r, ql);
}

int main() {
	int i, n, q, l, r, op, j;
	scanf("%d %d", &n, &q);
	scanf("%s", s);
	build(1, 0, n - 1);
	for(i = 0; i < q; i++) {
		scanf("%d %d", &op, &l); l--;
		if(op == 1) {
			scanf("%d", &r); r--;
			upd(1, 0, n - 1, l, r);
		} else {
			no.clear();
			query(1, 0, n - 1, l);
			int sum = 0, sz = 0;
			int best = 0;
			for(j = 0; j < no.size(); j++) {
				unlaze(no[j], L[no[j]], R[no[j]]);
				obj k = tr[no[j]];
				//printf("[%d, %d]: ", L[no[j]], R[no[j]]);
				//k.debug();
				if(k.mn + sum < 0) {
					//printf("BREAK\n");
					while(no.size() > j + 1) no.pop_back();
					if(L[no[j]] != R[no[j]]) no.pb(2 * no[j]);
					if(L[no[j]] != R[no[j]]) no.pb(2 * no[j] + 1);
					continue;
				}
				if(k.mn + sum == 0) best = k.tmn + sz;
				sum += k.sum;
				sz += k.sz;
			}
			printf("%d\n", best);
		}
	}
}
