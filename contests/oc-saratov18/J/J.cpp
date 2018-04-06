#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
//const ll modn = 1000000007;
const ll MOD = 1e9+7;
inline ll mod(ll x) { return x % MOD; }

const int N = 2e5+7;
const int K = 20;

int n, m, qs;
ll a[N];
int q[N][2];
ll dp[2][N][K];
ll res[N];

void go (int l, int r, vector<int> cur) {
	if (l == r) {
		for (int x : cur)
			res[x] = ((a[l]%m) == 0) + 1;
		return;
	}
	int p = (l+r)/2;

	for (int k = 0; k < m; k++) dp[0][p][k] = dp[1][p+1][k] = (k == 0);
	for (int i = p+1; i <= r; i++)
		for (int k = 0; k < m; k++) {
			dp[0][i][k] = (dp[0][i-1][k] + dp[0][i-1][(m+k-a[i])%m])%MOD;
		}
	for (int i = p; i >= l; i--) for (int k = 0; k < m; k++) dp[1][i][k] = (dp[1][i+1][k] + dp[1][i+1][(m+k-a[i])%m])%MOD;
	
	vector<int> lef, rig;
	for (int x : cur) {
		if (q[x][1] <= p) { lef.pb(x); }
		else if (q[x][0] > p) { rig.pb(x); } 
		else {
			for (int k = 0; k < m; k++)
				res[x] = mod(res[x] + mod(dp[1][q[x][0]][k]*dp[0][q[x][1]][(m-k)%m]));
		}
	}

	go(l,p,lef);
	go(p+1,r,rig);
}

int main () {
	scanf("%d %d", &n, &m);

	for (int i = 1; i <= n; i++) {
		scanf("%lld", &a[i]);
		a[i]%=m;
	}

	scanf("%d", &qs);
	vector<int> ini;
	for (int i = 0; i < qs; i++) {
		scanf("%d %d", &q[i][0], &q[i][1]);
		ini.pb(i);
	}

	go(1,n,ini);
	for (int i = 0; i < qs; i++) {
		printf("%lld\n", res[i]);
	}
}
