#include <vector>
#include <cstdio>
#include <cctype>
#include <algorithm>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }

template<class num> inline void rd(num &x) {
	char c;
	while(isspace(c = getchar()));
	bool neg = false;
	if(!isdigit(c)) neg = (c == '-'), x = 0;
	else x = c - '0';
	while(isdigit(c = getchar()))
		x = (x << 3) + (x << 1) + c - '0';
	if(neg) x = -x;
}

const int N = 212345;
int nx[N], he[N], to[N];

int lc[N][20], h[N];

int lca(int a, int b) {
	if(h[a] > h[b]) swap(a, b);
	for(int i = 0; h[a] != h[b]; i++)
		if((h[b] - h[a]) & (1 << i))
			b = lc[b][i];
	if(a == b) return a;
	for(int i = 16; i >= 0; i--)
		if(lc[a][i] != lc[b][i])
			a = lc[a][i],
			b = lc[b][i];
	return lc[a][0];
}

int en = 1;

void build(int u, int p, int h) {
	lc[u][0] = p;
	::h[u] = h;
	for(int j = 1; (1 << j) <= h; j++)
		lc[u][j] = lc[lc[u][j - 1]][j - 1];
	for(int e = he[u]; e; e = nx[e])
		if(to[e] != p)
			build(to[e], u, h + 1);
}

ll ans = 0;
ll m;
ll add[N];

ll go(int u, int p) {
	for(int e = he[u]; e; e = nx[e]) {
		int v = to[e];
		if(v == p) continue;
		add[u] += go(v, u);
	}
	if(u == 1) return 0;
	if(add[u] == 0) ans += m;
	else if(add[u] == 1) ans++;
	return add[u];
}

int main() {
	int i, n, a, b;
	rd(n); rd(m);
	for(i = 0; i < n - 1; i++) {
		rd(a); rd(b);
		to[en] = b; nx[en] = he[a]; he[a] = en++;
		to[en] = a; nx[en] = he[b]; he[b] = en++;
	}
	build(1, 1, 0);
	for(i = 0; i < m; i++) {
		rd(a); rd(b);
		int c = lca(a, b);
		add[a]++;
		add[b]++;
		add[c] -= 2;
	}
	go(1, 0);
	printf("%lld\n", ans);
}
