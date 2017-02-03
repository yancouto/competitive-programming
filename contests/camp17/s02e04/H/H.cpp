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
#	define debug(args...) {}
#else
#	define debug(args...) fprintf(stderr, args)
#endif

int n;
const int N = 201;
int adj[N][N];
bitset<N> bm[N];

int recalc() {
	int i, j;
	for(i = 0; i < n; i++)
		bm[i].reset(), bm[i][i] = 1;
	int tot = 0;
	for(i = n - 2; i >= 0; i--) {
		for(j = i + 1; j < n; j++)
			if(adj[i][j])
				bm[i] |= bm[j];
		tot += bm[i].count() - 1;
	}
	return tot;
}

int main() {
#ifdef ONLINE_JUDGE
	freopen("settling.in", "r", stdin);
	freopen("settling.out", "w", stdout);
#endif
	int i, j, a, b, m; char op;
	scanf("%d %d", &n, &m);
	for(i = 0; i < m; i++) {
		scanf("%d %d", &a, &b); a--; b--;
		adj[a][b] = 1;
	}
	printf("%d\n", recalc());
	scanf("%d", &m);
	while(m--) {
		scanf(" %c %d %d", &op, &a, &b); a--; b--;
		if(op == '+') {
			adj[a][b] = 1;
			printf("%d\n", recalc());
		} else if(op == '-') {
			adj[a][b] = 0;
			printf("%d\n", recalc());
		} else {
			if(bm[a][b]) puts("YES");
			else puts("NO");
		}
	}
}
