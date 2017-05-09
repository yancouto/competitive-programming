#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef pair<ll, ll> pii;

const int N = 303;
const ll MOD = 1e9+7;

int n;
int v[N];
int memo[N][N][N][2][2];
int adj[N][N];

inline ll mod (ll x) {
	return x%MOD;
}

ll pd (int i, int j, int k, int pi, int pj) {
	if (i + 1 == j) return 1;
	if (!pi && !pj) return 0;
	if (k == j) return 0;

	int & me = memo[i][j][k][pi][pj];
	if (me != -1) return me;

	me = pd(i,j,k+1,pi,pj);
	if (adj[i][k] && pi)
		me = mod(me + mod(pd(i,k,i+1,1,1)*pd(k,j,k+1,1,pj)));
	if (adj[j][k] && pj)
		me = mod(me + mod(pd(i,k,i+1,0,1)*pd(k,j,k+1,1,1)));
	
	return me;
}

int main () {
	memset(memo, -1, sizeof memo);
	scanf("%d", &n);

	for (int i = 0; i < n; i++)
		scanf("%d", &v[i]);
	
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			adj[i][j] = (__gcd(v[i], v[j]) != 1);

	printf("%lld\n", pd(0, n, 1, 1, 0));
}
