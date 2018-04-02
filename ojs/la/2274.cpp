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

const int N = 11234;

#define left left_

int ins[N], left[N];

int x[N], c[N], R[N], p[N], accp[N], l[N], r[N];
int dp[112][N];

int main() {
	int i, j, n, m;
	int tt = 0;
	while(scanf("%d %d", &n, &m) != EOF && n) {
		for(i = 1; i < n; i++)
			scanf("%d", &x[i]);
		for(i = 0; i < n; i++)
			scanf("%d", &c[i]);
		for(i = 0; i < n; i++)
			scanf("%d", &R[i]);
		for(i = 0; i < n; i++)
			scanf("%d", &p[i]);
		for(i = 0; i < n; i++)
			l[i] = lower_bound(x, x + n, x[i] - R[i]) - x,
			r[i] = (upper_bound(x, x + n, x[i] + R[i]) - x) - 1;
		accp[0] = p[0];
		for(i = 1; i < n; i++)
			accp[i] = accp[i - 1] + p[i];
		int ans = accp[n - 1]; // no post offices
		for(i = 0; i < n; i++)
			dp[1][i] = c[i] + accp[n - 1] - accp[r[i]];
		for(j = 1; ;) {
			// update
			for(i = 0; i < n; i++) ins[i] = left[i] = 5e8;
			for(i = 0; i < n; i++) {
				ins[l[i]] = min(ins[l[i]], dp[j][i]);
				left[l[i]] = min(left[l[i]], dp[j][i] + (l[i]? accp[l[i] - 1] : 0));
				ans = min(ans, dp[j][i] + (l[i]? accp[l[i] - 1] : 0));
			}
			for(i = 1; i < n; i++)
				ins[i] = min(ins[i], ins[i - 1]);
			for(i = n - 2; i >= 0; i--)
				left[i] = min(left[i], left[i + 1]);
			if(j == m) break;
			j++;
			// create
			for(i = 0; i < n; i++) {
				dp[j][i] = c[i] + ins[r[i]];
				if(r[i] != n - 1)
					dp[j][i] = min(dp[j][i], c[i] + left[r[i] + 1] - accp[r[i]]);
			}
		}
		printf("Case %d: %d\n", ++tt, ans);
	}
}
