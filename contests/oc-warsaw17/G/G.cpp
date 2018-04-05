#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> pii;
#define pb push_back

const int N = 1e5+7;
int dp[N][2]; // inc, dec
int lst[N][2];

int ts, n;
int v[N];

void _max (int i, int k, int x, int l) {
	if (dp[i][k] > x) return;
	dp[i][k] = x;
	lst[i][k] = l;
}
void _min (int i, int k, int x, int l) {
	if (dp[i][k] < x) return;
	dp[i][k] = x;
	lst[i][k] = l;
}

int main () {
	scanf("%d", &ts);
	while (ts--) {
		scanf("%d", &n);
		
		v[0] = 0;
		for (int i = 1; i <= n; i++)
			scanf("%d", &v[i]);

		dp[0][0] = n+1;
		dp[0][1] = 0;
		for (int i = 1; i <= n; i++) {
			dp[i][0] = 0;
			if (v[i-1] < v[i]) _max(i,0,dp[i-1][0],0);
			if (dp[i-1][1] < v[i]) _max(i,0,v[i-1],1);
			dp[i][1] = n+1;
			if (v[i-1] > v[i]) _min(i,1,dp[i-1][1],1);
			if (dp[i-1][0] > v[i]) _min(i,1,v[i-1],0);
		}

		stack<int> rs[2];
		bool t = 0;
		if (dp[n][t] == 0) {
			t = 1;
		}
		if (t && dp[n][t] == n+1) {
			printf("NO\n");
			continue;
		}

		while (n) {
			int nx = lst[n][t];
			rs[t].push(v[n]);
			t = nx;
			n--;
		}
		
		printf("YES\n");
		for (int k = 0; k < 2; k++) {
			printf("%d", (int) rs[k].size());
			while (rs[k].size()) { printf(" %d",rs[k].top()); rs[k].pop(); }
			printf("\n");
		}
	}
}
