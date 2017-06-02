#include <bits/stdc++.h>
using namespace std;
#define pb push_back
typedef long long ll;
#define x first
#define y second
#define minus adsasd
typedef pair<int, int> pt;
typedef pair<int, int> pii;

struct ret {
	pt a, b;
	bool good;
	bool operator < (ret o) const { return make_pair(a, b) < make_pair(o.a, o.b); }
	bool operator == (ret o) const { return make_pair(a, b) == make_pair(o.a, o.b); }
};

vector<ret> v;

pii minus(pii a, pii b) { return pii(a.x - b.x, a.y - b.y); }
pii sign(pii a) { return pii((a.x > 0) - (a.x < 0), (a.y > 0) - (a.y < 0)); }
pii dir(pii a, pii b) { return sign(minus(a, b)); }

ret inter(ret p, ret q) {
	if(p.a > p.b) swap(p.a, p.b);
	if(q.a > q.b) swap(q.a, q.b);
	if(q.a == q.b) swap(p, q);
	if(p.a == p.b) {
		if(p.a == q.a || p.a == q.b) return p;
		pii A = minus(p.a, q.a), B = minus(q.b, q.a);
		if(ll(A.x) * ll(B.y) != ll(A.y) * ll(B.x)) return {p.a, p.a, false};
		if(p.a >= q.a && p.a <= q.b) return p;
		return {p.a, p.b, false};
	}
	if(dir(p.a, p.b) == dir(q.a, q.b)) {
		if(p.b.y > p.a.y) {
			if(p.a.x - p.a.y != q.a.x - q.a.y) return {p.a, p.a, false};
		} else {
			if(p.a.x + p.a.y != q.a.x + q.a.y) return {p.a, p.a, false};
		}
		ret c = {max(p.a, q.a), min(p.b, q.b), true};
		if(c.a > c.b) c.good = false;
		return c;
	} else {
		if(q.b.y > q.a.y) swap(p, q);
		int xmy = p.a.x - p.a.y;
		int xpy = q.a.x + q.a.y;
		if((xmy + xpy) % 2) return {p.a, p.b, false};
		pii c = pii((xmy + xpy) / 2, (xpy - xmy) / 2);
		if(c >= p.a && c <= p.b && c >= q.a && c <= q.b) return {c, c, true};
		else return {p.a, p.b, false};
	}
}

int main() {
	int i, n, j, k, d, x, y;
	scanf("%d", &n);
	scanf("%d %d %d", &x, &y, &d);
	if(d == 0) v.pb({pii(x, y), pii(x, y), true});
	else {
		v.pb({pii(x + d, y), pii(x, y + d), true});
		v.pb({pii(x + d, y), pii(x, y - d), true});
		v.pb({pii(x - d, y), pii(x, y + d), true});
		v.pb({pii(x - d, y), pii(x, y - d), true});
	}
	for(i = 1; i < n; i++) {
		vector<ret> v2, v3;
		scanf("%d %d %d", &x, &y, &d);
		v2.pb({pii(x + d, y), pii(x, y + d), true});
		v2.pb({pii(x + d, y), pii(x, y - d), true});
		v2.pb({pii(x - d, y), pii(x, y + d), true});
		v2.pb({pii(x - d, y), pii(x, y - d), true});
		for(ret a : v)
			for(ret b : v2) {
				ret c = inter(a, b);
				if(c.good) v3.pb(c);
			}
		v.clear();
		for(j = 0; j < v3.size(); j++) {
			for(k = j + 1; k < v3.size(); k++)
				if(v3[j] == v3[k]) break;
			if(k == v3.size()) v.pb(v3[j]);
		}
	}
	if(v.empty()) puts("impossible");
	else if(v.size() > 1 || v.back().a != v.back().b) puts("uncertain");
	else printf("%d %d\n", v.back().a.x, v.back().a.y);
}
