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

struct ev {
	int when, l, r; int x;
	bool operator < (ev o) const {
		if(when != o.when)
			return when < o.when;
		else return x < o.x;
	}
};

const int M = 2000000009;
int en = 1;

const int N = 21234567;
inline void fix(int &u) {
	if(u) return;
	assert(en < N);
	u = en++;
}

int tr[N], lz[N]; int L[N], R[N];

inline void unlaze(int &i, int l, int r) {
	fix(i);
	if(!lz[i]) return;
	//printf("lz (%d, %d) += %d\n", l, r, lz[i]);
	tr[i] += lz[i];
	if(l != r) {
		fix(L[i]); fix(R[i]);
		lz[L[i]] += lz[i];
		lz[R[i]] += lz[i];
	}
	lz[i] = 0;
}

int go(int &i, int l, int r, int ql, int qr, int x) {
	unlaze(i, l, r);
	if(r < ql || l > qr) return tr[i];
	if(l >= ql && r <= qr) {
		lz[i] = x;
		unlaze(i, l, r);
		return tr[i];
	}
	ll m = (r - l) / 2 + l;
	go(L[i], l, m, ql, qr, x);
	go(R[i], m + 1, r, ql, qr, x);
	return tr[i] = max(tr[L[i]], tr[R[i]]);
}

ll c[712345]; int cn;

inline int get(ll x) { return lower_bound(c, c + cn, x) - c; }

int main() {
	int i, n; ll l, r;
	scanf("%d %lld %lld", &n, &l, &r);
	for(i = 0; i < n; i++) {
		scanf("%lld %lld %d", &x[i], &y[i], &s[i]);
		c[cn++] = y[i];
		c[cn++] = y[i] + 2 * r;
		c[cn++] = y[i] + 2 * r - (r - l) = 1;
		c[cn++] = y[i] + r - l + 1;
	}
	sort(c, c + cn);
	cn = unique(c, c + cn) - c;
	vector<ev> evs;
	for(i = 0; i < n; i++) {
		ll x = ::x[i], y = ::y[i]; int s = ::s[i];
		// pt 1
		evs.pb(ev{int(min<ll>(x, M)), int(y), int(min<ll>(y + 2 * r, M)), (s)});
		// pt 2
		evs.pb(ev{int(min<ll>(x + r - l + 1,M)), int(min<ll>(y + r - l + 1, M)), int(min<ll>(y + 2 * r - (r - l) - 1, M)), -(s)});
		// pt 3
		evs.pb(ev{int(min<ll>(x + 2 * r - (r - l),M)), int(min<ll>(y + r - l + 1, M)), int(min<ll>(y + 2 * r - (r - l) - 1, M)), (s)});
		evs.pb(ev{int(min<ll>(x + 2 * r + 1, M)), int(y), int(min<ll>(y + 2 * r, M)), -(s)});
	}
	sort(evs.begin(), evs.end());
	ll best = 0;
	int root = 0;
	for(ev e : evs) {
		best = max<ll>(best, go(root, 0, M, e.l, e.r, e.x));
		//deb(root, 0, M);
		//printf(" [%d] (%d, %d) += %d best now %d\n", e.when, e.l, e.r, e.x, best);
	}
	printf("%lld\n", best);
}
