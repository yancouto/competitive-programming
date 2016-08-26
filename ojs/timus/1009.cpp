#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll memo[18][2];
int n, k;
ll solve(int i, bool prev0) {
	if(i == n) return 1;
	ll &r = memo[i][prev0];
	if(r != -1) return r;
	r = 0;
	for(int d = 0; d < k; d++) {
		if(prev0 && d == 0) continue;
		r += solve(i + 1, d == 0);
	}
	return r;
}


int main() {
	scanf("%d %d", &n, &k);
	memset(memo, -1, sizeof memo);
	printf("%lld\n", solve(0, true));
}
