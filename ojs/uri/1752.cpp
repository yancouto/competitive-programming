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
const int MAX = 509;
int R, C;
int ro[MAX][MAX], co[MAX][MAX], v[MAX][MAX];

inline int l(int i) { return i << 1; }
inline int r(int i) { return l(i) + 1; }
set<pii> ts[MAX << 2];

void build(int i, int le, int ri) {
	ts[i].clear();
	if(le == ri) {
		for(int j = 0; j < C; j++)
			ts[i].insert(pii(j, le));
		return;
	}
	int mi = (le + ri) / 2;
	build(l(i), le, mi);
	build(r(i), mi + 1, ri);
	for(pii p : ts[l(i)])
		ts[i].insert(p);
	for(pii p : ts[r(i)])
		ts[i].insert(p);
}

void remove(int i, int le, int ri, pii p) {
	ts[i].erase(p);
	if(le == ri) return;
	int mi = (le + ri) / 2;
	if(p.x <= mi) remove(l(i), le, mi, p);
	else remove(r(i), mi + 1, ri, p);
}

void query(int i, int le, int ri, int x1, int x2, int y1, int y2, vector<pii> &v) {
	if(le > x2 || ri < x1) return;
	if(le >= x1 && ri <= x2) {
		auto it = ts[i].lower_bound(pii(y1, INT_MIN));
		while(it != ts[i].end() && it->x <= y2)
			v.pb(*it++);
		return;
	}
	int mi = (le + ri) / 2;
	query(l(i), le, mi, x1, x2, y1, y2, v);
	query(r(i), mi + 1, ri, x1, x2, y1, y2, v);
}

struct no {
	int x, y, d;
	no() {}
	no(int a, int b, int c) : x(a), y(b), d(c) {}
	bool operator < (no o) const { return d + v[x][y] < o.d + v[o.x][o.y]; }
};

int solve(int x1, int y1, int x2, int y2) {
	build(1, 0, R - 1);
	priority_queue<no> pq;
	pq.push(no(x1, y1, 0));
	remove(1, 0, R - 1, pii(y1, x1));
	while(!pq.empty()) {
		no n = pq.top(); pq.pop();
		if(n.x == x2 && n.y == y2) return n.d;
		vector<pii> v;
		int rr = ro[n.x][n.y], cc = co[n.x][n.y];
		query(1, 0, R - 1, n.x - rr, n.x + rr, n.y - cc, n.y + cc, v);
		for(pii p : v) {
			remove(1, 0, R - 1, p);
			pq.push(no(p.y, p.x, n.d + ::v[n.x][n.y]));
		}
	}
	return -1;
}

int main() {
	int n, i, j;
	scanf("%d %d %d", &R, &C, &n);
	for(i = 0; i < R; i++)
		for(j = 0; j < C; j++)
			scanf("%d", &v[i][j]);
	for(i = 0; i < R; i++)
		for(j = 0; j < C; j++)
			scanf("%d", &ro[i][j]);
	for(i = 0; i < R; i++)
		for(j = 0; j < C; j++)
			scanf("%d", &co[i][j]);
	int lr, lc, cr, cc;
	for(i = 0; i < n; i++) {
		scanf("%d %d", &cr, &cc); cr--; cc--;
		if(i)
			printf("%d\n", solve(lr, lc, cr, cc));
		lr = cr; lc = cc;
	}
}
