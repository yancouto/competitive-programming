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


namespace f {
	const int N = 11234, M = 11234 * 2;
	typedef int num;
	num inf = INT_MAX;
	int n = N;
	
	int to[M], en, nx[M], es[M], lv[N], qu[N], cr[N];
	num cp[M], fl[M];

	bool bfs(int s, int t) {
		memset(lv, -1, sizeof(int) * n);
		lv[s] = 0;
		int a = 0, b = 0;
		qu[b++] = s; cr[s] = es[s];
		while(a < b) {
			for(int i = es[qu[a]]; i != -1; i = nx[i])
				if(cp[i] > fl[i] && lv[to[i]] == -1) {
					lv[to[i]] = lv[qu[a]] + 1;
					qu[b++] = to[i];
					cr[to[i]] = es[to[i]];
					if(to[i] == t) return true;
				}
			a++;
		}
		return false;
	}

	num dfs(int u, int t, num mx) {
		if(u == t) return mx;
		for(int &i = cr[u]; i != -1; i = nx[i])
			if(cp[i] > fl[i] && lv[to[i]] == lv[u] + 1)
				if(num a = dfs(to[i], t, min(mx, cp[i] - fl[i]))) {
					fl[i] += a;
					fl[i ^ 1] -= a;
					return a;
				}
		return 0;
	}

	num max_flow(int s, int t) {
		num fl = 0, a;
		while(bfs(s, t)) {
			for(int i = 0; i < n; i++) cr[i] = es[i];
			while(a = dfs(s, t, inf)) {
				fl += a;
			}
		}
		return fl;
	}
	
	void reset_all(int n2=N) { n = n2; en = 0; memset(es, -1, sizeof(int) * n); }
	void reset_flow() { memset(fl, 0, sizeof(num) * en); }

	void add_edge(int a, int b, num c, num rc = 0) {
		fl[en] = 0; to[en] = b; cp[en] = c;  nx[en] = es[a]; es[a] = en++;
		fl[en] = 0; to[en] = a; cp[en] = rc; nx[en] = es[b]; es[b] = en++;
	}
}


const int N = 50;

int n, m, w[N], d[N][N];
string nm[N];

void solve(int u) {
	int tot = w[u], rest = 0, i, j;
	for(i = 0; i < n; i++)
		tot += d[u][i];
	f::reset_all();
	int p = n * n;
	for(i = 0; i < n; i++)
		if(i != u)
			f::add_edge(f::N - 1, i, w[i]),
			f::add_edge(i, f::N - 2, tot),
			rest += w[i];
	for(i = 0; i < n; i++)
		for(j = i + 1; j < n; j++) {
			if(i == u || j == u || !d[i][j]) continue;
			rest += d[i][j];
			f::add_edge(f::N - 1, p + i * n + j, d[i][j]);
			f::add_edge(p + i * n + j, i, f::inf);
			f::add_edge(p + i * n + j, j, f::inf);
		}
	int f = f::max_flow(f::N - 1, f::N - 2);
	if(f == rest) {
		printf("%s can win\n", nm[u].c_str());
		return;
	}
	printf("%s cannot win because of the following teams:\n", nm[u].c_str());
	vector<int> v;
	for(i = 0; i < n; i++)
		if(i != u && f::lv[i] != -1 /* ou mudar */)
			v.pb(i);
	printf("    ");
	for(i = 0; i < v.size(); i++) {
		printf("%s", nm[v[i]].c_str());
		if(i != v.size() - 1) printf(", ");
	}
	putchar('\n');
}

char s[N];
int main() {
#ifdef ONLINE_JUDGE
	freopen("high.in", "r", stdin);
	freopen("high.out", "w", stdout);
#endif
	int i, j;
	scanf("%d", &n);
	for(i = 0; i < n; i++) {
		scanf("%s %d", s, &w[i]);
		nm[i] = s;
	}
	for(i = 0; i < n; i++)
		for(j = 0; j < n; j++)
			scanf("%d", &d[i][j]);
	for(i = 0; i < n; i++)
		solve(i);
}
