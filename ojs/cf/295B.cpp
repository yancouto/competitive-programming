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

int ford[3][506][507];
int adj[508][505];
int x[507], y[509];
ll st[509]; int sn;

int main(int argn, char **args) {
	int i, j, n, k;
	scanf("%d", &n);
	for(i = 0; i < n; i++)
		for(j = 0; j < n; j++)
			scanf("%d", &adj[i][j]);
	for(i = 0; i < n; i++) {
		scanf("%d", &x[i]);
		x[i]--;
	}
	reverse(x, x + n);
	for(i = 0; i < n; i++)
		y[x[i]] = i;
	for(i = 0; i < n; i++)
		for(j = 0; j < n; j++)
			ford[1][i][j] = adj[x[i]][x[j]];
	for(k = 0; k < n; k++) {
		ll tot = 0;
		for(i = 0; i < n; i++)
			for(j = 0; j < n; j++) {
				ford[k & 1][i][j] = min(ford[!(k&1)][i][j], ford[!(k&1)][i][k] + ford[!(k&1)][k][j]);
				if(i <= k && j <= k)
					tot += ford[k & 1][i][j];
			}
		st[sn++] = tot;
	}
	while(sn) printf("%lld ", st[--sn]);
	putchar('\n');
}
