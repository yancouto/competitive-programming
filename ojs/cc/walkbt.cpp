#include <bits/stdc++.h>
using namespace std;

//#define debug(args...) printf(args)
#define debug(args...) ((void) 0)
typedef long long ll;

struct hsh {
	ll x;
	ll y;
	ll z;

	inline bool operator < (hsh o) const {
		if(x != o.x) return x < o.x;
		if(y != o.y) return y < o.y;
		return z < o.z;
	}
	inline bool operator == (hsh o) const { return x == o.x && y == o.y && z == o.z; }
	inline void reset() { x = 0; y = 1; z = 2; }
	inline void join(hsh a, hsh b, int l, int m, int r);
	inline void set(int x) { this->x = x; this->y = x + 1; this->z = x + 2; }
};

const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }
const ll modn2 = 1000000009;
inline ll mod2(ll x) { return x % modn2; }
const ll modn3 = 1000000021;
inline ll mod3(ll x) { return x % modn3; }

const int N = 112345;

ll pot[N], pot2[N], pot3[N];

void hsh::join(hsh a, hsh b, int l, int m, int r) {
	int sz = (r - (m + 1)) + 1;
	int sz2 = m - l + 1;
	x = mod(a.x * pot[sz] + b.x);
	y = mod2(a.y * pot2[sz] + b.y);
	z = mod3(a.z + b.z * pot3[sz2]);
	//debug("join(%d, %d) = %d\n", a.x, b.x, x);
}

const int M = 31234567;
int n;

hsh tr[M];
int L[M], R[M];
int en = 1;

inline int cp(int i) {
	int j = en++;
	assert(j < M);
	//printf("%d->%d\n", i, j);
	tr[j] = tr[i];
	L[j] = L[i];
	R[j] = R[i];
	return j;
}

int set_(int oi, int l, int r, int p, int x) {
	int i = cp(oi);
	if(l == r) { tr[i].set(x); return i; }
	int m = (l + r) / 2;
	if(p <= m) L[i] = set_(L[i], l, m, p, x);
	else R[i] = set_(R[i], m + 1, r, p, x);
	//printf("will join at %d(%d, %d)\n", i, l, r);
	tr[i].join(tr[L[i]], tr[R[i]], l, m, r);
	return i;
}

int get(int i, int l, int r, int p) {
	if(l == r) return tr[i].x;
	int m = (l + r) / 2;
	if(p <= m) return get(L[i], l, m, p);
	else return get(R[i], m + 1, r, p);
}

int lcp(int A, int B, int l, int r) {
	debug(" A (%d,%d) and B(%d,%d) in [%d,%d]\n", tr[A].x, tr[A].y, tr[B].x, tr[B].y, l, r);
	if(tr[A] == tr[B]) return r + 1;
	if(l == r) return l;
	int m = (l + r) / 2;
	if(tr[L[A]] == tr[L[B]]) return lcp(R[A], R[B], m + 1, r);
	else return lcp(L[A], L[B], l, m);
}

inline int new_nodes(int A, int B) {
	debug("new_nodes(%d, %d) = %d - %d\n", A, B, n, lcp(A, B, 0, n - 1));
	return n - lcp(A, B, 0, n - 1);
}

struct cmp_seg {
	bool operator()(int A, int B) {
		if(A == B) return false;
		int l = lcp(A, B, 0, n - 1);
		debug("lcp(%d, %d) = %d nx A%d vs B%d\n", A, B, l, get(A, 0, n - 1, l), get(B, 0, n - 1, l));
		if(l == n) return false;
		int dA = get(A, 0, n - 1, l), dB = get(B, 0, n - 1, l);
		assert(dA != dB);
		return dA < dB;
	}
};

int build(int l, int r) {
	int i = en++;
	tr[i].reset();
	if(l == r) return i;
	int m = (l + r) / 2;
	L[i] = build(l, m);
	R[i] = build(m + 1, r);
	tr[i].join(tr[L[i]], tr[R[i]], l, m, r);
	return i;
}


int a[N];

int main() {
	char op;
	int i, t, q;
	pot[0] = pot2[0] = pot3[0] = 1;
	for(i = 1; i < N; i++)
		pot[i] = mod(pot[i - 1] * 3ll),
		pot2[i] = mod2(pot2[i - 1] * 7ll),
		pot3[i] = mod3(pot3[i - 1] * 247ll);
	scanf("%d", &t);
	while(t--) {
		scanf("%d %d", &n, &q);
		ll tot = 1;
		set<int, cmp_seg> seg;
		set<hsh> hs;
		for(i = 0; i < en; i++) tr[i].reset(), L[i] = R[i] = 0;
		en = 1;
		for(i = 0; i < n; i++) a[i] = 0;
		int cur = build(0, n - 1);
		while(q--) {
			scanf(" %c", &op);
			if(op == '!') {
				scanf("%d", &i); i = n - 1 - i;
				while(i >= 0 && a[i] == 1) {
					debug("a[%d] = 0\n", i);
					a[i] = 0;
					cur = set_(cur, 0, n - 1, i--, 0);
				}
				if(i >= 0) debug("a[%d] = 1\n", i);
				if(i >= 0) cur = set_(cur, 0, n - 1, i, 1), a[i] = 1;
				debug("tr[%d] = %lld\n", cur, tr[cur].x);
				debug("tr[%d] = %lld\n", cur, tr[cur].y);
				if(!hs.insert(tr[cur]).second) continue;
				auto it = seg.lower_bound(cur);
				debug("rm part\n");
				if(it != seg.end()) {
					if(it == seg.begin()) tot -= n, debug("tot -= %d\n", n + 1);
					else tot -= new_nodes(*prev(it), *it), debug("tot -= %d\n", new_nodes(*prev(it), *it));
				}
				if(it == seg.begin()) tot += n, debug("tot += %d\n", n + 1);
				else tot += new_nodes(*prev(it), cur), debug("tot += %d\n", new_nodes(*prev(it), cur));
				if(it != seg.end()) tot += new_nodes(cur, *it), debug("tot  += %d\n", new_nodes(cur, *it));
				seg.insert(cur);
			} else {
				printf("%lld\n", tot);
			}
		}
	}
}
