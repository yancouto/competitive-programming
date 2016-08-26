#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef unsigned long long ull;
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
template<typename T> inline T abs(T t) { return t < 0? -t : t; }
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }

ll tot;

struct ev {
	int y, cr, x;
	bool operator < (ev o) const { return y < o.y; }
};
struct ret {
	int y, x1, x2;
};
typedef map<int, map<int, int> > grid;

void sweep(grid &mp, vector<ev> &es, vector<ret> &rs, bool add) {
	for(auto &e : mp) {
		int cur = 0;
		int last = -1;
		for(auto &p : e.snd) {
			if(last == -1) last = p.fst;
			cur += p.snd;
			if(cur == 0) {
				printf("[%d] seg %d -- %d\n", add, last, p.fst - 1);
				tot += p.fst - last;
				if(add) {
					es.pb(ev{last, 1, e.fst});
					es.pb(ev{p.fst, -1, e.fst});
				} else rs.pb(ret{e.fst, last, p.fst - 1});
				last = -1;
			}
		}
	}
}

int c[200009 + 200009], cn;
int bit[400009];
void add(int i, int x) {
	for(i += 2; i < 400009; i += (i & -i))
		bit[i] += x;
}
int get(int i) {
	int sum = 0;
	for(i += 2; i; i -= (i & -i))
		sum += bit[i];
	return sum;
}
inline int get(int i, int j) { return get(j) - get(i - 1); }

inline int comp(int x) { return lower_bound(c, c + cn, x) - c; }
int main() {
	int i, x1, x2, y1, y2, n;
	scanf("%d", &n);
	grid mpx, mpy;
	for(i = 0; i < n; i++) {
		scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
		if(x1 > x2) swap(x1, x2);
		if(y1 > y2) swap(y1, y2);
		if(x1 == x2) mpy[x1][y1]++, mpy[x1][y2+1]--;
		else mpx[y1][x1]++, mpx[y1][x2+1]--;
	}
	vector<ev> es;
	vector<ret> rs;
	sweep(mpx, es, rs, false);
	sweep(mpy, es, rs, true);
	sort(es.begin(), es.end());
	int cur = 0;
	for(i = 0; i < rs.size(); i++)
		c[2*i] = rs[i].x1, c[2*i + 1] = rs[i].x2;
	for(i = 0; i < es.size(); i++)
		c[2* rs.size() + i] = es[i].x;
	sort(c, c + 2 * rs.size() + es.size());
	cn = unique(c, c + 2 * rs.size() + es.size()) - c;
	for(i = 0; i < es.size(); i++)
		es[i].x = comp(es[i].x);
	for(i = 0; i < rs.size(); i++) {
		rs[i].x1 = comp(rs[i].x1);
		rs[i].x2 = comp(rs[i].x2);
		while(cur < es.size() && es[cur].y <= rs[i].y) {
			add(es[cur].x, es[cur].cr);
			cur++;
		}
		tot -= get(rs[i].x1, rs[i].x2);
	}
	printf("%I64d\n", tot);
}
