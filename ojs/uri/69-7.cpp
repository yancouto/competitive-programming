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

namespace f {
	const int maxv = 300;
	const int maxe = (101 * 101 + 300) * 2;
	typedef int num;
	num inf = INT_MAX;
	int n = maxv;

	int to[maxe], en, nx[maxe], es[maxe], lv[maxv], qu[maxv];
	num cp[maxe], fl[maxe];


	bool bfs(int s, int t) {
		memset(lv, -1, sizeof(int) * n);
		lv[s] = 0;
		int a = 0, b = 0;
		qu[b++] = s;
		while(a < b) {
			for(int i = es[qu[a]]; i != -1; i = nx[i]) {
				if(cp[i] > fl[i] && lv[to[i]] == -1) {
					lv[to[i]] = lv[qu[a]] + 1;
					qu[b++] = to[i];
					if(to[i] == t) return true;
				}
			}
			a++;
		}
		return false;
	}

	int us[maxv], te, cr[maxv];
	num dfs(int u, int t, num mx) {
		if(u == t) return mx;
		if(us[u] == te) return 0;
		us[u] = te;
		for(int &i = cr[u]; i != -1; i = nx[i]) {
			if(cp[i] > fl[i] && lv[to[i]] == lv[u] + 1) {
				if(int a = dfs(to[i], t, min(mx, cp[i] - fl[i]))) {
					fl[i] += a;
					fl[i ^ 1] -= a;
					return a;
				}
			}
		}
		return 0;
	}


	num max_flow(int s, int t) {
		num fl = 0, a;
		while(bfs(s, t)) {
			te++;
			for(int i = 0; i < n; i++) cr[i] = es[i];
			while(a = dfs(s, t, inf))
				fl += a, te++;
		}
		return fl;
	}

	void reset_all(int n2=maxv) { n = n2; en = 0; memset(es, -1, sizeof(int) * n); }
	void reset_flow(int m=maxe/2) { memset(fl, 0, sizeof(num) * m*2); }

	void add_edge(int a, int b, num c, num rc=0) {
		fl[en] = 0; to[en] = b; cp[en] = c;  nx[en] = es[a]; es[a] = en++;
		fl[en] = 0; to[en] = a; cp[en] = rc; nx[en] = es[b]; es[b] = en++;
	}
}
int sa[102][102], sb[102][102];
int san[102], sbn[102];
int memo[103][103];
int solve(int i, int j, int a, int b) {
	if(i == san[a] || j == sbn[b]) return 0;
	int &r = memo[i][j];
	if(r != -1) return r;
	if(sa[a][i] == sb[b][j]) return r = 1 + solve(i + 1, j + 1, a, b);
	r = max(solve(i + 1, j, a, b), solve(i, j + 1, a, b));
	return r;
}


bool ok(int i, int j) {
	memset(memo, -1, sizeof memo);
	int lcs = solve(0, 0, i, j);
	if((((san[i] - lcs) + (sbn[j] - lcs)) % 5) == 0) return true;
	return false;
}
char s1[200]; int g[27];
int main() {
	int n, m, i, j;
	while(true) {
		f::reset_all();
		scanf("%d %d", &n, &m);
		if(!n) return 0;
		for(i = 0; i < n; i++) {
			scanf("%s", s1);
			memset(g, 0, sizeof g);
			for(j = 0; s1[j]; j++)
				sa[i][j] = (s1[j] - 'A' + 1) + 26 * g[s1[j] - 'A']++;
			san[i] = j;
			f::add_edge(0, i + 1, 1);
		}
		for(i = 0; i < m; i++) {
			scanf("%s", s1);
			memset(g, 0, sizeof g);
			for(j = 0; s1[j]; j++)
				sb[i][j] = (s1[j] - 'A' + 1) + 26 * g[s1[j] - 'A']++;
			sbn[i] = j;
			f::add_edge(f::maxv - 2 - i, f::maxv - 1, 1);
		}
		for(i = 0; i < n; i++)
			for(j = 0; j < m; j++)
				if(ok(i, j))
					f::add_edge(i + 1, f::maxv - 2 - j, 1);
		int x = f::max_flow(0, f::maxv - 1);
		printf("P = %.2f\n", (double(100 * x) / n));
	}
}
