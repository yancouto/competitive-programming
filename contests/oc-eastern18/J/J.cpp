#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int  N = 100123;

vector<pii> v[N];
int n; ll c;
ll dp[N];


int gettime() {
	int a, b, c;
	scanf(" %d:%d:%d", &a, &b, &c);
	return a*60*60 + b*60 + c;
}

int main () {
	scanf("%d %lld", &n, &c);

	for (int i = 0; i < n; i++) {
		int a = gettime();
		pii res;
		res.second = gettime();
		scanf("%lld", &res.first);
		res.first -= c*(res.second-a);
		v[a].pb(res);
	}

	for (int i = N-1; i >= 0; i--) {
		dp[i] = 0;
		for (pii t : v[i])
			dp[i] = max(dp[i], dp[t.second] + t.first);
		if (i < N-1) dp[i] = max(dp[i], dp[i+1]);
	}

	printf("%lld\n", dp[0]);
}
