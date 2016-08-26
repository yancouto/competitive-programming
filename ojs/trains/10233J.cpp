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

#include <cmath>
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
	num dist_sqr(ptn o) const { return (*this - o) * (*this - o); }
	bool operator < (ptn o) const { return x < o.x || (x == o.x && y < o.y); }
};
typedef point<int> pti;
temp inline num cross(ptn a, ptn b, ptn c) { return (c - a) ^ (b - a); }
const int N = 612345;

pti p[N]; int a[N], b[N], c[N], pai[512]; double d[N], dist[512], C[N], A[N];
const double eps = 1e-7;
int adj[512][512];

int n, m;
int pos(double k) {
	for(int i = 0; i < m; i++)
		C[i] = k * d[i] - A[i];
	memset(dist, 0, sizeof dist);
	for(int i = 0; i < n; i++) pai[i] = i;
	for(int i = 0; i < n; i++)
		for(int j = 0; j < m; j++)
			if(dist[b[j]] > dist[a[j]] + C[j]) {
				dist[b[j]] = dist[a[j]] + C[j];
				pai[b[j]] = a[j];
			}
	for(int j = 0; j < m; j++)
		if(dist[b[j]] > dist[a[j]] + C[j])
			return b[j] + 1;
	return 0;
}



int seen[512];

bool dfs(int u, int p) {
	if(seen[u]) return true;
	seen[u] = true;
	for(int v = 0; v < n; v++)
		if(p != v && adj[u][v] != -1 && dfs(v, u))
			return true;
	return false;
}

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	int i;
	scanf("%d %d", &n, &m);
	for(i = 0; i < n; i++)
		scanf("%d %d %d", &p[i].x, &p[i].y, &c[i]);
	memset(adj, -1, sizeof adj);
	for(i = 0; i < m; i++) {
		scanf("%d %d %lf", &a[2*i], &b[2*i], &d[2*i]); a[2*i]--, b[2*i]--;
		d[2*i] += (c[a[2*i]] + c[b[2*i]]) / 2.;
		adj[a[2*i]][b[2*i]] = 2*i;
		adj[b[2*i]][a[2*i]] = 2*i + 1;
		a[2*i+1] = b[2*i]; b[2*i+1] = a[2*i]; d[2*i+1] = d[2*i];
	}
	m *= 2;
	for(i = 0; i < n; i++)
		if(!seen[i] && dfs(i, i))
			break;
	if(i == n) { puts("Barrayar in danger"); return 0; }
	memset(seen, 0, sizeof seen);
	for(i = 0; i < m; i++)
		A[i] = (p[a[i]] ^ p[b[i]]) / 2.;
	double l = 0, r = 1e6;
	while(clock() < CLOCKS_PER_SEC * 1.6) {
		double m = (l + r) / 2.;
		if(pos(m)) l = m;
		else r = m;
	}
	assert(r - l <= 1e-5);
	int b = pos(l) - 1;
	assert(b >= 0);
	while(!seen[b]) {
		seen[b] = 1;
		b = pai[b];
	}
	vector<int> v;
	while(seen[b] != 2) {
		seen[b] = 2;
		v.pb(b);
		b = pai[b];
	}
	printf("%d\n", (int) v.size());
	ll tot = 0;
	for(i = 1; i < v.size() - 1; i++) tot += cross(p[v[0]], p[v[i]], p[v[i + 1]]);
	if(tot > 0) reverse(v.begin(), v.end());
	for(int x : v) printf("%d ", x + 1);
	putchar('\n');
}
