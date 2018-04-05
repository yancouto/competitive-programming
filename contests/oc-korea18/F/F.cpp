#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll,ll> pii;

const int N = 15;

int n;
ll adj[N][N];
ll memo[N][(1<<N)];

int submask (int a, int b) {
	int i = 0, r = 0;
	while (b) {
		while (!(a&(1<<i))) i++;
		if (b&1) r += (1<<i);
		b >>= 1;
		i++;
	}
	return r;
}

int main () {
	scanf("%d", &n);

	for (int i = 0; i < n; i++) {
		for (int j = i+1; j < n; j++) {
			scanf("%lld", &adj[i][j]);
			adj[j][i] = adj[i][j];
		}
	}

	for (int msk = 0; msk < (1<<(n-1)); msk++) {
		for (int u = 0; u < n; u++) if (!((1<<u)&msk)) {
			ll & me = memo[u][msk];
			if (!msk) me = 0;
			else {
				me = LLONG_MAX;
				int s = __builtin_popcount(msk);
				for (int sub = msk; true; sub = ((sub-1)&msk)) {
					int t = __builtin_popcount(sub);
					ll rs = ll((t+1)*(n-t-1));
					for (int v = 0; v < n; v++) if ((msk&(1<<v)) && !(sub&(1<<v)))
						me = min(me, memo[v][sub] + memo[u][msk-sub-(1<<v)] + rs*adj[u][v]);
					if (sub == 0) break;
				}
			}
		}
	}

	printf("%lld\n", memo[n-1][(1<<(n-1))-1]);
}
