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
const int N = 11234;
int seen[N], he[N], nx[N], to[N], cp[N], fl[N], p[N], path[3002][3002], t, en;
int n, m;

bool dfs(int a, int b) {
	if(a == b) return true;
	if(seen[a] == t) return false;
	seen[a] = t;
	for(int e = he[a]; e != -1; e = nx[e])
		if(cp[e] - fl[e] && dfs(to[e], b)) {
			fl[e]++;
			fl[e ^ 1]--;
			return true;
		}
	return false;
}

int flow(int a, int b) {
	for(int i = 0; i < en; i++) fl[i] = 0;
	int all = 0; t++;
	while(dfs(a, b)) all++, t++;
	return all;
}

int main() {
	int i, j, a, b;
	while(scanf("%d %d", &n, &m) != EOF) {
		en = 0;
		for(i = 0; i < n; i++) he[i] = -1, p[i] = 0, path[i][i] = 1e9;
		for(i = 0; i < m; i++) {
			scanf("%d %d", &a, &b); a--; b--;
			to[en] = b; cp[en] = 1; fl[en] = 0; nx[en] = he[a]; he[a] = en++;
			to[en] = a; cp[en] = 1; fl[en] = 0; nx[en] = he[b]; he[b] = en++;
		}
		int tot = 0;
		for(i = 1; i < n; i++) {
			int v = flow(i, p[i]);
			for(j = i + 1; j < n; j++)
				if(seen[j] == t && p[j] == p[i])
					p[j] = i;
			for(j = 0; j < i; j++) {
				path[i][j] = path[j][i] = min(path[j][p[i]], v);
				tot += path[j][i];
			}
		}
		printf("%d\n", tot);
	}
}
