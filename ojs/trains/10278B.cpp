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

int main() {
	scanf("%d %d", &n, &m);
	for(i = 0; i < n; i++)
		for(j = 0; j < m; j++)
			scanf(" %c", &g[i][j]);
	int ans = solve(g, n, m);
	for(i = 0; i < n; i++)
		for(j = 0; j < m; j++)
			if(g[i][j] == '>') a[j][i] = 'v';
			else if(g[i][j] == 'v') a[j][i] = '<';
			else if(g[i][j] == '<') a[j][i] = '^';
			else a[j][i] = '>';
	printf("%d\n", ans + solve(a, m, n));
}
