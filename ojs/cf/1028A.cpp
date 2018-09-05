#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }
#ifdef ONLINE_JUDGE
#	define debug(args...) ((void) 0)
#else
#	define debug(args...) fprintf(stderr, args)
#endif

int n, m;
char g[212][212];

int main() {
	int i, j;
	scanf("%d %d", &n, &m);
	int ci = -1, cj = -1;
	for(i = 0; i < n; i++) {
		int xl = -1, xr = -1;
		for(j = 0; j < m; j++) {
			scanf(" %c", &g[i][j]);
			if(g[i][j] == 'B') xr = j;
			if(g[i][j] == 'B' && xl == -1) xl = j;
		}
		if(xl != -1) cj = (xl + xr) / 2;
	}
	for(j = 0; j < m; j++) {
		int xl = -1, xr = -1;
		for(i = 0; i < n; i++) {
			if(g[i][j] == 'B') xr = i;
			if(g[i][j] == 'B' && xl == -1) xl = i;
		}
		if(xl != -1) ci = (xl + xr) / 2;
	}
	printf("%d %d\n", ci + 1, cj + 1);
}
