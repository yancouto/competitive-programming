#include <bits/stdc++.h>
using namespace std;
#define pb push_back

typedef long long ll;
typedef pair<ll,ll> pii;

const int N = 53;

ll MOD;
ll mx;
int n, q;
ll dp[2][N][N];
ll acc[2][N][N];

int main () {
	scanf("%d", &q);
	while (q--) {
		scanf("%d %lld %lld", &n, &mx, &MOD);

		for (int i = 0; i <= mx; i++) {
			int w = (i&1);
			if (i == 0) {
				for (int r = 1; r <= n; r++)
					for (int s = n; s >= 1; s--) {
						dp[w][r][s] = (r == 1 && s == n);
						acc[w][r][s] = (acc[w][r][s+1] + dp[w][r][s])%MOD;
					}
			} else {
				ll res = 0;
				for (int r = 1; r <= n; r++) {
					for (int s = n; s >= 1; s--) {
						dp[w][r][s] = 0;
						int t = n-s+1;
						if (t <= r && r <= i+1 && i <= r*(r-1)/2 + t*(t-1)/2) {
							if (r <= i) dp[w][r][s] = (dp[w][r][s] + dp[!w][r][s])%MOD;
							else dp[w][r][s] = (dp[w][r][s] + dp[!w][r-1][s])%MOD;
							dp[w][r][s] = (dp[w][r][s] + acc[!w][r][s+1])%MOD;
							if (t == r || r == i+1 || r == n) res = (res + dp[w][r][s])%MOD;
						}
						//cout << "(" << i << " " << r << " " << s << ") = " << dp[w][r][s] << endl;
						acc[w][r][s] = (acc[w][r][s+1] + dp[w][r][s])%MOD;
					}
				}
				//printf("%lld ", res);
				res = 0;
				for(int s = 1; s <= n; s++)
					res = (res + dp[w][min(i + (s == n), n)][s]) % MOD;
				printf("%lld ", res);
			}
		}
		printf("\n");
	}
}
