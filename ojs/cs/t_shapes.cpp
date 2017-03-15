#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }

char g[203][203];

int main() {
	int i, j, n, m;
	scanf("%d %d", &n, &m);
	for(i = 0; i < n; i++)
		for(j = 0; j < m; j++)
			scanf(" %c", &g[i][j]);
	int ct = 0;
	for(i = 0; i < n - 2; i++)
		for(j = 0; j < m - 2; j++)
			if(g[i][j] == 't' && g[i][j + 1] == 't' && g[i][j + 2] == 't' && g[i + 1][j + 1] == 't' && g[i + 2][j + 1] == 't')
				ct++;
	printf("%d\n", ct);
}
