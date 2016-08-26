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

char adj[1002][1002];
int seen[1002], cmp, n;
vector<int> cs[1003];

void dfs(int u) {
	if(seen[u]) return;
	seen[u] = 1;
	cs[cmp].pb(u);
	for(int i = 0; i < n; i++)
		if(adj[u][i] == 'S')
			dfs(i);
}
int a[1003];

int main() {
	int i, j, k;
	scanf("%d", &n);
	for(i = 0; i < n; i++)
		for(j = 0; j < n; j++)
			scanf(" %c", &adj[i][j]);
	for(i = 0; i < n; i++)
		if(!seen[i]) {
			dfs(i);
			cmp++;
		}
	for(i = 0; i < cmp; i++) {
		for(j = 0; j < cs[i].size(); j++)
			for(k = 0; k < cs[i].size(); k++)
				if(adj[cs[i][j]][cs[i][k]] != 'S') {
					puts("-1");
					return 0;
				}
		a[i] = cs[i].size();
	}
	sort(a, a + cmp);
	printf("%d\n%d", cmp, a[cmp-1]);
	for(i = cmp - 2; i >= 0; i--)
		printf(" %d", a[i]);
	putchar('\n');
	return 0;
}
