#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef pair<int, int> pii;
typedef unsigned long long ull;
typedef long long ll;
typedef long double ld;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
template<typename T> inline T abs(T t) { return t < 0? -t : t; }
const ull modn = 1000000007;
inline ull mod(ull x) { return x % modn; }
#define temp template<typename num>
#define ptn point<num>
temp struct point {
	num x, y;
	ptn() {}
	ptn(num a, num b) : x(a), y(b) {}
	ptn operator + (ptn o) const { return ptn(x + o.x, y + o.y); }
	ptn operator - (ptn o) const { return ptn(x - o.x, y - o.y); }
	num operator * (ptn o) const { return x * o.x + y * o.y; }
	num operator ^ (ptn o) const { return x * o.y - y * o.x; }
	ptn operator * (num i) const { return ptn(x * i, y * i); }
	ptn operator / (num i) const { return ptn(x / i, y / i); }
	point<double> rotate(double deg) {
		double cs = cos(deg), sn = sin(deg);
		return point<double>(x*cs - y*sn, x*sn + y*cs);
	}
	num distSqr(ptn o) const { return (*this - o) * (*this - o); }
	bool operator < (ptn o) const { return x < o.x || (x == o.x && y < o.y); }
};
temp inline num cross(ptn a, ptn b, ptn c) { return (b - a) ^ (c - a); }

typedef point<ll> pti;

pti ps[40009][2];
ll wa[40009];
const int MAX = 1000009;
vector<int> evin[MAX], evout[MAX];
vector<int> adj[40009];

struct cmp {
	bool operator() (int i, int j) {
		bool a = cross(ps[i][0], ps[i][1], ps[j][0]) > 0;
		bool b = cross(ps[i][0], ps[i][1], ps[j][1]) > 0;
		if(!(a ^ b)) return a;
		return cross(ps[j][0], ps[j][1], ps[i][0]) < 0;
	}
};
int deg[40009], n;

ll dfs(int u) {
	for(int v : adj[u])
		wa[u] += dfs(v);
	return wa[u];
}

int main() {
	int i;
	for_tests(t, tt) {
		scanf("%d", &n);
		if(tt > 1) putchar('\n');
		memset(deg, 0, sizeof deg);
		memset(wa, 0, sizeof wa);
		for(i = 0; i < n; i++) {
			scanf("%lld %lld %lld %lld", &ps[i][0].x, &ps[i][0].y, &ps[i][1].x, &ps[i][1].y);
			evin[ps[i][0].x].pb(i);
			evout[ps[i][1].x].pb(i);
			wa[i] = 0; adj[i].clear();
		}
		set<int, cmp> cur;
		for(i = 0; i < MAX; i++) {
			if(!cur.empty()) { wa[*cur.rbegin()]++; }
			sort(evin[i].begin(), evin[i].end(), cmp());
			for(int s : evin[i]) {
				auto o = cur.insert(s).fst;
				if(ps[s][0].y < ps[s][1].y && o != cur.begin()) {
					adj[*(--o)].pb(s);
					deg[s]++;
				}
			}
			sort(evout[i].begin(), evout[i].end(), cmp());
			reverse(evout[i].begin(), evout[i].end());
			for(int s : evout[i]) {
				auto o = cur.find(s); auto oo = o;
				if(ps[s][0].y > ps[s][1].y && o != cur.begin()) {
					adj[*(--o)].pb(s);
					deg[s]++;
				}
				cur.erase(oo);
			}
			evin[i].clear(); evout[i].clear();
		}
		for(i = 0; i < n; i++)
			if(!deg[i])
				dfs(i);
		for(i = 0; i < n; i++)
			printf("%lld\n", wa[i]);
	}
	return 0;
}
