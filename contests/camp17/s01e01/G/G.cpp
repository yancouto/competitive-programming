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
#	define debug(args...) {}
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

const int N = 212345;

vector<ll*> all;
ll o[N];
int n, an;

ll tr[4 * N];

void build(int i, int l, int r) {
	tr[i] = LLONG_MAX;
	if(l == r) return;
	int m = (l + r) / 2;
	build(2 * i, l, m);
	build(2 * i + 1, m + 1, r);
}

ll lz[4 * N];
void unlaze(int i, int l, int r) {
	if(tr[i] == LLONG_MAX) { lz[i] = 0; return; }
	tr[i] += lz[i];
	if(l != r) lz[2 * i] += lz[i], lz[2 * i + 1] += lz[i];
	lz[i] = 0;
}

void upd(int i, int l, int r, int p, ll v) {
	//for(int g = 1; g <= 8; g++) printf("%lld |", tr[g]); putchar('\n');
	unlaze(i, l, r);
	if(l == r) { tr[i] = v; return; }
	int m = (l + r) / 2;
	if(p <= m) upd(2 * i, l, m, p, v);
	else upd(2 * i + 1, m + 1, r, p, v);
	unlaze(2 * i, l, m);
	unlaze(2 * i + 1, m + 1, r);
	tr[i] = min(tr[2 * i], tr[2 * i + 1]);
	//printf("%lld,%lld\n", tr[2*i], tr[2*i+1]);
	//printf("r[%d] = %lld\n", i, tr[i]);
}

void add(int i, int l, int r, int ql, int qr, ll v) {
	unlaze(i, l, r);
	if(l > qr || r < ql) return;
	if(l >= ql && r <= qr) {
		lz[i] = v;
		unlaze(i, l, r);
		return;
	}
	int m = (l + r) / 2;
	add(2 * i, l, m, ql, qr, v);
	add(2 * i + 1, m + 1, r, ql, qr, v);
	tr[i] = min(tr[2 * i], tr[2 * i + 1]);
}

int st[N];

ll bit[N];
void add(int i, ll x) {
	for(i += 2; i < N; i += (i & -i))
		bit[i] += x;
}

ll get(int i) {
	ll x = 0;
	for(i += 2; i; i -= (i & -i))
		x += bit[i];
	return x;
}

int go(int i, int l, int r) {
	unlaze(i, l, r);
	if(tr[i] > 0ll) return 0;
	if(l == r) return 1;
	int m = (l + r) / 2;
	return go(2 * i, l, m) + go(2 * i + 1, m + 1, r);
}

void rem(int x) {
	upd(1, 0, an, x, LLONG_MAX);
	add(x, -o[x]);
	add(1, 0, an, x + 1, an, -o[x]);
}

void add(int x) {
	//printf("%d need %d\n", x, need);
	upd(1, 0, an, x, get(x - 1) - o[x]);
	add(1, 0, an, x + 1, an, o[x]);
	add(x, o[x]);
}

ll f[N], fk[N], k[N];

int main() {
	int i, j, m;
	rd(n);
	for(i = 0; i < n; i++)
		rd(f[i]), all.pb(&f[i]);
	rd(m);
	for(i = 0; i < m; i++) {
		rd(k[i]); k[i]--; rd(fk[i]);
		all.pb(&fk[i]);
	}
	sort(all.begin(), all.end(), [](ll *x, ll *y) { return (*x) < (*y); });
	an = all.size() - 1;
	for(i = 0; i < all.size(); i++)
		o[i] = *all[i];
	for(i = 0; i < all.size(); i++)
		*all[i] = i;
	ll cur = 0;
	build(1, 0, an);
	for(i = 0; i < n; i++)
		add(f[i]);
	printf("%d\n", go(1, 0, an));
	for(i = 0; i < m; i++) {
		rem(f[k[i]]);
		add(fk[i]);
		f[k[i]] = fk[i];
		printf("%d\n", go(1, 0, an));
	}
}
