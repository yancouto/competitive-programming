#include <bits/stdc++.h>
using namespace std;
#define x first
#define y second
typedef unsigned long long ull;
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
template<typename T> inline T abs(T t) { return t < 0? -t : t; }
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }
const int MAX = 100009;
inline int L(int i) { return i << 1; }
inline int R(int i) { return L(i) + 1; }

struct per {
	int i; pii p;
	per() {}
	per(int a, int b, int c) : i(a + 1), p(b + c, b - c) {}
	per(int yy) : i(0), p(0, yy) {}
	bool operator < (per o) const { return p.y != o.p.y? p.y < o.p.y : i < o.i; }
};

multiset<per> ts[MAX << 2];
vector<per> pt[MAX];
void build(int i, int le, int ri) {
	ts[i].clear();
	if(le == ri) {
		for(per p : pt[le])
			ts[i].insert(p);
		pt[le].clear();
		return;
	}
	int mi = (le + ri) / 2;
	build(L(i), le, mi);
	build(R(i), mi + 1, ri);
	for(per p : ts[L(i)])
		ts[i].insert(p);
	for(per p : ts[R(i)])
		ts[i].insert(p);
}

void query(int i, int le, int ri, int x1, int x2, int y1, int y2, vector<per> &v) {
	if(le > x2 || ri < x1) return;
	if(le >= x1 && ri <= x2) {
		auto it = ts[i].lower_bound(per(y1));
		while(it != ts[i].end() && it->p.y <= y2)
			v.pb(*it++);
		return;
	}
	int mi = (le + ri) / 2;
	query(L(i), le, mi, x1, x2, y1, y2, v);
	query(R(i), mi + 1, ri, x1, x2, y1, y2, v);
}

void ch(bool rem, int i, int le, int ri, per p) {
	if(rem) ts[i].erase(p);
	else ts[i].insert(p);
	if(le == ri) return;
	int mi = (le + ri) / 2;
	if(p.p.x <= mi) ch(rem, L(i), le, mi, p);
	else ch(rem, R(i), mi + 1, ri, p);
}

void add(int i, int le, int ri, per p) { ch(false, i, le, ri, p); }
void remove(int i, int le, int ri, per p) { ch(true, i, le, ri, p); }

int main() {
	ll i, n, q, w, h, a, b, c, d, e, f, xx, yy, sz;
	for_tests(t, tt) {
		scanf("%lld %lld %lld %lld", &n, &q, &w, &h);
		for(i = 0; i < n; i++) {
			scanf("%lld %lld", &xx, &yy);
			pt[xx + yy].pb(per(i, xx, yy));
		}
		build(1, 0, MAX - 1);
		for(i = 0; i < q; i++) {
			scanf("%lld %lld %lld %lld %lld %lld %lld %lld %lld", &xx, &yy, &sz, &a, &b, &c, &d, &e, &f);
			vector<per> v;
			query(1, 0, MAX - 1, xx + yy - sz, xx + yy + sz, xx - yy - sz, xx - yy + sz, v);
			for(per &pe : v) {
				remove(1, 0, MAX - 1, pe);
				pii &p = pe.p;
				p = pii((p.x + p.y) / 2, (p.x - p.y) / 2);
				p = pii((ll(p.x) * a + ll(p.y) * b + c * ll(pe.i)) % w, (ll(p.x) * d + ll(p.y) * e + ll(pe.i) * f) % h);
				p = pii(p.x + p.y, p.x - p.y);
				add(1, 0, MAX - 1, pe);
			}
		}
		printf("Case #%d:\n", tt);
		vector<per> v;
		for(per pe : ts[1]) {
			pii &p = pe.p;
			p = pii((p.x + p.y) / 2, (p.x - p.y) / 2);
			v.pb(pe);
		}
		sort(v.begin(), v.end(), [](per p, per p2) { return p.i < p2.i; });
		for(per pe : v)
			printf("%d %d\n", pe.p.x, pe.p.y);
	}
}
