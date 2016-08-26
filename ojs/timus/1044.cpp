#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll m[20][100];
ll s(int n, int sum) {
	if(n == 0) return sum == 0;
	if(m[n][sum]) return m[n][sum];
	ll ans = 0;
	for(int i = 0; i <= 9; i++)
		ans += s(n - 1, sum - i);
	return m[n][sum] = ans;
}

int main() {
	int n;
	scanf("%d", &n);
	ll ans = 0, i;
	for(i = 0; i < 100; i++)
		ans += s(n / 2, i) * s(n / 2, i);
	printf("%lld\n", ans);
	return 0;
}
