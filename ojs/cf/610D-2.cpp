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

typedef map<int, map<int, int> > grid;

struct ev { int y, x, cr; };
struct re { int y, x1, x2; };
ll tot = 0;

void sweep(grid &g, bool x, vector<ev> &evs, vector<re> &res) {
	for(auto &e : g) {
		int cur = 0, prev = -1;
		for(auto &p : e.snd) {
			if(prev == -1) prev = p.fst;
			cur += p.snd;
			if(cur) continue;
			if(x) {
				evs.pb(ev{prev, e.fst, 1});
				evs.pb(ev{p.fst, e.fst, -1});
			} else res.pb(re{e.fst, prev, p.fst - 1});
			tot += ll(p.fst) - ll(prev);
			prev = -1;
		}
	}
}

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

int c[400009], cn;
inline int comp(int x) { return lower_bound(c, c + cn, x) - c; }

int main() {
	int i, n, x1, x2, y1, y2;
	scanf("%d", &n);
	grid mpx, mpy;
	for(i = 0; i < n; i++) {
		scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
		if(x1 > x2) swap(x1, x2);
		if(y1 > y2) swap(y1, y2);
		if(x1 == x2) mpx[x1][y1]++, mpx[x1][y2 + 1]--;
		else mpy[y1][x1]++, mpy[y1][x2 + 1]--;
	}
	vector<ev> evs; vector<re> res;
	sweep(mpx, false, evs, res);
	sweep(mpy, true, evs, res);
	sort(evs.begin(), evs.end(), [](ev a, ev b) { return a.y < b.y; });
	for(ev &e : evs) c[cn++] = e.x;
	for(re &r : res) c[cn++] = r.x1, c[cn++] = r.x2;
	sort(c, c + cn);
	cn = unique(c, c + cn) - c;
	int cur = 0;
	for(re &r : res) {
		while(cur < evs.size() && evs[cur].y <= r.y) {
			add(comp(evs[cur].x), evs[cur].cr);
			cur++;
		}
		tot -= ll(get(comp(r.x1), comp(r.x2)));
	}
	printf("%lld\n", tot);
}
