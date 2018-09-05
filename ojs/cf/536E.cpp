#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }
#ifdef ONLINE_JUDGE
#	define debug(args...) ((void) 0)
#else
#	define debug(args...) fprintf(stderr, args)
#endif

template<class num> inline void rd(num &x) {
	char c;
	while(isspace(c = getchar()));
	bool neg = false;
	if(!isdigit(c)) neg = (c == '-'), x = 0;
	else x = c - '0';
	while(isdigit(c = getchar()))
		x = (x << 3) + (x << 1) + c - '0';
	if(neg) x = -x;
}

struct dat {
	int l, r;
	int sum;
	bool full;
};

const int N = 112345;
const int M = N << 2;

int f[N];

dat join(dat a, dat b, bool d=false) {
	if(d) debug("(%d, %d, %d, %d) + (%d, %d, %d, %d)", a.l, a.r, a.sum, a.full, b.l, b.r, b.sum, b.full);
	dat c;
	c.full = a.full && b.full;
	c.sum = a.sum + b.sum;
	if(c.full) {
		c.l = c.r = a.l + b.l;
	} else if(a.full) {
		c.l = a.r + b.l;
		c.r = b.r;
	} else if(b.full) {
		c.l = a.l;
		c.r = a.r + b.l;
	} else {
		c.l = a.l;
		c.r = b.r;
		c.sum += f[a.r + b.l];
	}
	if(d) debug(" = (%d, %d, %d, %d)\n", c.l, c.r, c.sum, c.full);
	return c;
}

dat tr[M];
int L[M], R[M];
int en = 1;

int build(int l, int r) {
	int i = en++;
	assert(i < M);
	if(l == r) return i;
	int m = (l + r) / 2;
	L[i] = build(l, m);
	R[i] = build(m + 1, r);
	return i;
}

int h[N], pai[N], sz[N];
int ch[N], ci[N], cs[N], seg[N];

vector<pii> adj[N];

int get_sz(int u, int c, int p, int h) {
	pai[u] = p;
	::h[u] = h;
	if(u) adj[u].erase(search_n(adj[u].begin(), adj[u].end(), 1, pii(p, c)));
	sz[u] = 1;
	for(pii e : adj[u])
		sz[u] += get_sz(e.fst, e.snd, u, h + 1);
	return sz[u];
}

int we[N];

void go(int u, int c, int w) {
	ch[u] = c;
	ci[u] = cs[c]++;
	we[u] = w;

	int h = -1; int css;
	for(pii e: adj[u])
		if(h == -1 || sz[h] < sz[e.fst])
			h = e.fst, css = e.snd;
	
	if(h == -1) {
		seg[c] = build(0, cs[c] - 1);
		return;
	}

	go(h, c, css);
	for(pii e : adj[u])
		if(e.fst != h)
			go(e.fst, e.fst, e.snd);
}

void set1(int i, int l, int r, int p) {
	if(l == r) return (void)(tr[i] = dat{1, 1, 0, true});
	int m = (l + r) / 2;
	if(p <= m) set1(L[i], l, m, p);
	else set1(R[i], m + 1, r, p);
	tr[i] = join(tr[L[i]], tr[R[i]]);
	//debug("[%d..%d] = l %d r %d sum %d full %d\n", l, r, tr[i].l, tr[i].r, tr[i].sum, int(tr[i].full));
}

dat get(int i, int l, int r, int ql, int qr) {
	if(l > qr || r < ql) return dat{0, 0, 0, true};
	if(l >= ql && r <= qr) return tr[i];
	int m = (l + r) / 2;
	dat l_ = get(L[i], l, m, ql, qr);
	dat r_ = get(R[i], m + 1, r, ql, qr);
	//debug("%d..%d + %d..%d\n", l, m, m + 1, r);
	return join(l_, r_);
}

dat swap(dat a) {
	swap(a.l, a.r);
	return a;
ould print T(b) for this query.}

int ans[N];

int solve(int a, int b) {
	dat l{0, 0, 0, true}, r{0, 0, 0, true};
	while(ch[a] != ch[b]) {
		if(h[ch[a]] > h[ch[b]]) {
			l = join(get(seg[ch[a]], 0, cs[ch[a]] - 1, 0, ci[a]), l, 1);
			a = pai[ch[a]];
		} else {
			r = join(get(seg[ch[b]], 0, cs[ch[b]] - 1, 0, ci[b]), r, 1);
			b = pai[ch[b]];
		}
	}
	if(h[a] > h[b]) {
		assert(ci[b] < ci[a]);
		l = join(get(seg[ch[a]], 0, cs[ch[a]] - 1, ci[b] + 1, ci[a]), l, 1);
	} else if(h[b] > h[a]) {
		assert(ci[a] < ci[b]);
		r = join(get(seg[ch[b]], 0, cs[ch[b]] - 1, ci[a] + 1, ci[b]), r, 1);
	}
	dat d = join(l, swap(r), 1);
	return d.full? f[d.l] : d.sum + f[d.l] + f[d.r];
}

int a[N], b[N], c[N], p[N], pu[N];

void solve(int i) {
	ans[i] = solve(a[i], b[i]);
	debug("ans[%d] = solve(%d, %d) = %d\n", i + 1, a[i] + 1, b[i] + 1, ans[i]);
}


int main() {
	int i, n, q;
	rd(n); rd(q);
	for(i = 1; i <= n - 1; i++) rd(f[i]);
	for(i = 0; i < n - 1; i++) {
		int a, b, c;
		rd(a); rd(b); rd(c); a--; b--;
		adj[a].pb(pii(b, c));
		adj[b].pb(pii(a, c));
	}
	get_sz(0, 0, 0, 0);
	go(0, 0, 0);

	for(i = 0; i < q; i++) {
		rd(a[i]); rd(b[i]); rd(c[i]); a[i]--; b[i]--;
		p[i] = i;
	}
	sort(p, p + q, [](int i, int j) { return c[i] > c[j]; });
	for(i = 0; i < n - 1; i++) pu[i] = i + 1;
	sort(pu, pu + n - 1, [](int i, int j) { return we[i] > we[j]; });
	int l = 0;
	for(int i_ = 0; i_ < n - 1; i_++) {
		i = pu[i_];
		while(l < q && we[i] < c[p[l]]) {
			solve(p[l++]);
		}
		debug("set1(%d) p %d\n", i + 1, ci[i]);
		set1(seg[ch[i]], 0, cs[ch[i]] - 1, ci[i]);
	}
	while(l < q) solve(p[l++]);
	for(i = 0; i < q; i++)
		printf("%d\n", ans[i]);
}
