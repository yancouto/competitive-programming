#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll modn = 1000000007;
ll f[212345];

int main() {
	int i, n, k;
	scanf("%d %d", &n, &k);
	for(i = 1; i <= k; i++) f[i] = i;
	for(i = k + 1; i <= n; i++) {
		f[i] = f[i - 1] - f[i - k - 1];
		f[i] = (f[i] + f[i - 1] + modn) % modn;
	}
	printf("%lld\n", (f[n] - f[n - 1] + modn) % modn);
}
