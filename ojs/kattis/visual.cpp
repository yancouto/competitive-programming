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

struct pt {
	int i, j;
	int id;
	bool operator < (pt o) const {
		if(i != o.i) return i < o.i;
		return j < o.j;
	}
	bool operator > (pt o) const {
		return !(*this < o);
	}
};

const int N = 412345;
pt ul[N], dr[N];

void imp() {
	puts("syntax error");
	exit(0);
}

vector<int> tmp;

int il[N], ir[N], jl[N], jr[N]; int rn;

set<pii> tr[N << 2];
void add(int i, int l, int r, int ai, int aj, int a, bool ad) {
	if(ad) tr[i].insert(pii(aj, a));
	else tr[i].erase(pii(aj, a));
	if(l == r) return;
	int m = (l + r) / 2;
	if(ai <= m) add(2 * i, l, m, ai, aj, a, ad);
	else add(2 * i + 1, m + 1, r, ai, aj, a, ad);
}

void get(int i, int l, int r, int a) {
	if(l > ir[a] || r < il[a]) return;
	if(l >= il[a] && r <= ir[a]) {
		for(auto it = tr[i].lower_bound(pii(jl[a], INT_MIN)); it != tr[i].end() && it->fst <= jr[a]; ++it)
			tmp.pb(it->snd);
		return;
	}
	int m = (l + r) / 2;
	get(2 * i, l, m, a);
	get(2 * i + 1, m + 1, r, a);
}

inline bool inside(int a, int b) {
	return il[a] > il[b] && ir[a] < ir[b] && jl[a] > jl[b] && jr[a] < jr[b];
}

void add_rect(int i) {
	//printf("%d: (%d, %d) x (%d, %d)\n", i, il[i], ir[i], jl[i], jr[i]);
	tmp.clear();
	get(1, 1, N, i);
	sort(tmp.begin(), tmp.end());
	tmp.erase(unique(tmp.begin(), tmp.end()), tmp.end());
	for(int x : tmp) {
		add(1, 1, N, il[x], jl[x], x, false);
		add(1, 1, N, il[x], jr[x], x, false);
		if(!inside(x, i))
			imp();
	}
	add(1, 1, N, il[i], jl[i], i, true);
	add(1, 1, N, il[i], jr[i], i, true);
}

int c[N << 2], cn;
int ans[N];

struct cmp {
	bool operator()(pt a, pt b) {
		if(a.j != b.j) return a.j < b.j;
		return a.i < b.i;
	}
};

int main() {
	int i, n;
	scanf("%d", &n);
	for(i = 0; i < n; i++) {
		scanf("%d %d", &ul[i].i, &ul[i].j), ul[i].id = i;
		c[cn++] = ul[i].i;
		c[cn++] = ul[i].j;
	}
	for(i = 0; i < n; i++) {
		scanf("%d %d", &dr[i].i, &dr[i].j), dr[i].id = i;
		c[cn++] = dr[i].i;
		c[cn++] = dr[i].j;
	}
	sort(c, c + cn);
	cn = unique(c, c + cn) - c;
	for(i = 0; i < n; i++) {
		ul[i].i = lower_bound(c, c + cn, ul[i].i) - c;
		ul[i].j = lower_bound(c, c + cn, ul[i].j) - c;
		dr[i].i = lower_bound(c, c + cn, dr[i].i) - c;
		dr[i].j = lower_bound(c, c + cn, dr[i].j) - c;
		//printf("ul[%d] = (%d, %d)\n", i, ul[i].i, ul[i].j);
		//printf("dr[%d] = (%d, %d)\n", i, dr[i].i, dr[i].j);
	}
	sort(ul, ul + n, greater<pt>());
	sort(dr, dr + n, greater<pt>());
	set<pt, cmp> d;
	int bn = 0;
	for(i = 0; i < n; i++) {
		while(bn < n && ul[i] < dr[bn])
			d.insert(dr[bn++]);
		if(d.empty()) imp();
		auto it = d.lower_bound(ul[i]);
		if(it == d.end()) imp();
		ans[ul[i].id] = it->id;
		il[rn] = ul[i].i;
		ir[rn] = it->i;
		jl[rn] = ul[i].j;
		jr[rn] = it->j;
		add_rect(rn++);
		d.erase(it);
	}
	for(i = 0; i < n; i++)
		printf("%d\n", ans[i] + 1);
}
