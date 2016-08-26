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

ll pot[4001000];
ll g[2005][2005];
ll f[2005][2005];
void pre() {
	pot[0] = 1;
	for(int i = 1; i < 4001000; i++)
		pot[i] = mod(pot[i - 1] * 263ll);
}

int main() {
	pre();
	int i, j, n, m, n2, m2; char c;
	while(scanf("%d %d %d %d", &n2, &m2, &n, &m) != EOF) {
		ll p = 0;
		for(i = 0; i < n2; i++)
			for(j = 0; j < m2; j++) {
				scanf(" %c", &c);
				p = mod(p + ll(c) * pot[i * m + j]);
			}
		for(i = 0; i < n; i++)
			for(j = 0; j < m; j++) {
				scanf(" %c", &c);
				f[i][j] = g[i][j] = mod(ll(c) * pot[i * m + j]);
			}
		for(i = 0; i < n; i++)
			for(j = 0; j < m; j++) {
				if(i) g[i][j] += g[i-1][j];
				if(j) g[i][j] += g[i][j-1];
				if(i && j) g[i][j] -= g[i-1][j-1];
				g[i][j] = mod(g[i][j] + modn);
			}
		int tot = 0;
		for(i = 0; i + n2 - 1 < n; i++)
			for(j = 0; j + m2 - 1 < m; j++) {
				ll x = g[i + n2 - 1][j + m2 - 1];
				if(i) x -= g[i-1][j + m2 - 1];
				if(j) x -= g[i + n2 - 1][j-1];
				if(i && j) x += g[i-1][j-1];
				x = mod(x + 2ll * modn);
				if(mod(p * pot[i * m + j]) == x) tot++;
			}
		printf("%d\n", tot);
	}
}
