#include <bits/stdc++.h>
using namespace std;
#define prt first
#define tim second
typedef unsigned long long ull;
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }
#ifdef ONLINE_JUDGE
#	define LLD "%I64d"
#	define debug(args...) {}
#else
#	define LLD "%lld"
#	define debug(args...) fprintf(stderr, args)
#endif
const int N = 1123;
int p[N], t[N][N], s[N], f[N], st[N], b[N][N];

const int M = 512 * 512 *2;
int fl[M], cp[M], nx[M], to[M], he[N], en = 2;
void add_edge(int a, int b) {
	cp[en] = 1; to[en] = b; nx[en] = he[a]; he[a] = en++;
	cp[en] = 0; to[en] = a; nx[en] = he[b]; he[b] = en++;
}

int tempo, seen[N];
bool dfs(int u, int t) {
	if(u == t) return true;
	if(seen[u] == tempo) return false;
	seen[u] = tempo;
	for(int e = he[u]; e; e = nx[e])
		if(cp[e] - fl[e] && dfs(to[e], t)) {
			fl[e]++; fl[e ^ 1]--;
			return true;
		}
	return false;
}

int flow(int s, int t) {
	int fl = 0; tempo++;
	while(dfs(s, t)) fl++, tempo++;
	return fl;
}

int main() {
	int i, j, n, m, k;
	scanf("%d %d", &n, &m);
	for(i = 0; i < n; i++) scanf("%d", &p[i]);
	for(i = 0; i < n; i++)
		for(j = 0; j < n; j++) {
			scanf("%d", &t[i][j]);
			t[i][j] += p[j];
			b[i][j] = t[i][j];
		}
	for(i = 0; i < n; i++) b[i][i] = t[i][i] = 0;
	for(k = 0; k < n; k++)
		for(i = 0; i < n; i++)
			for(j = 0; j < n; j++)
				t[i][j] = min(t[i][j], t[i][k] + t[k][j]);
	for(i = 0; i < m; i++) {
		scanf("%d %d %d", &s[i], &f[i], &st[i]); s[i]--; f[i]--;
		p[i] = i;
	}
	sort(p, p + m, [](int i, int j) { return st[i] < st[j]; });
	for(i = m - 1; i >= 0; i--)
		for(j = i + 1; j < m; j++)
			if(st[p[i]] + b[s[p[i]]][f[p[i]]] + t[f[p[i]]][s[p[j]]] <= st[p[j]])
				add_edge(i, j + m);
	for(i = 0; i < m; i++) add_edge(1100, i);
	for(i = 0; i < m; i++) add_edge(i + m, 1109);
	printf("%d\n", m - flow(1100, 1109));
}
