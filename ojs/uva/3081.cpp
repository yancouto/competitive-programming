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
	bool operator < (ptn o) const { return x + y < o.x + o.y || (x + y == o.x + o.y && y < o.y); }
};
temp inline num cross(ptn a, ptn b, ptn c) { return (c - a) ^ (b - a); }
temp inline bool betweenSeg(ptn a, ptn b, ptn c) { return cross(a, b, c) == 0 && ((b - c) * (a - c) <= 0); }
temp bool intersectSeg(ptn a, ptn b, ptn c, ptn d) {
	if(betweenSeg(a, b, c) || betweenSeg(a, b, d) || betweenSeg(c, d, a) || betweenSeg(c, d, b)) return true;
	if(((cross(a, b, c) > 0) ^ (cross(a, b, d) > 0)) && ((cross(c, d, a) > 0) ^ (cross(c, d, b) > 0))) return true;
	return false;
}
typedef point<ll> pti;

const int MAX = 2009;
pti ps[4009];
vector<int> adj[MAX];
bool intersect(int i, int j) {
	pti &a = ps[2*i], &b = ps[2*i+1], &c = ps[2*j], &d = ps[2*j+1];
	return intersectSeg(a, b, c, d);
}

int n;
int seen[MAX], d[MAX], low[MAX], tc, tempo;
vector<int> st;
int comp[MAX], ct;
bool ok;
void dfs(int u) {
	if(seen[u]) return;
	seen[u] = 1;
	d[u] = low[u] = tempo++;
	st.pb(u);
	for(int v : adj[u]) {
		dfs(v);
		low[u] = min(low[u], low[v]);
	}
	if(low[u] == d[u]) {
		int s; ct++;
		do {
			s = st.back(); st.pop_back();
			low[s] = INT_MAX;
			if(comp[s ^ 1] == ct) ok = false;
			comp[s] = ct;
		} while(s != u);
	}
}
int main() {
	int i, j;
	while(true) {
		st.clear();
		scanf("%d", &n);
		if(!n) return 0;
		for(i = 0; i < n; i++) {
			pti a[4];
			for(j = 0; j < 4; j++) scanf("%lld %lld", &a[j].x, &a[j].y);
			sort(a, a + 4);
			ps[4*i] = a[0];
			ps[4*i + 1] = a[3];
			ps[4*i + 2] = a[1];
			ps[4*i + 3] = a[2];
			adj[2*i].clear();
			adj[2*i + 1].clear();
		}
		for(i = 0; i < 2*n; i++)
			for(j = i + 1; j < 2*n; j++) {
				if(i == (j ^ 1)) continue;	
				if(intersect(i, j)) {
					adj[i].pb(j ^ 1);
					adj[j].pb(i ^ 1);
				}
			}
		ok = true;
		tempo = 0;
		memset(comp, 0, sizeof comp); ct = 0;
		memset(seen, 0, sizeof seen);
		for(i = 0; i < 2*n; i++)
			dfs(i);
		if(ok) puts("YES");
		else puts("NO");
	}
}
