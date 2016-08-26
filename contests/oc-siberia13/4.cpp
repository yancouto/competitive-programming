#include <bits/stdc++.h>

int main() {
	int n; long long a, b, p;
	scanf("%d", &n);
	if(n == 1) {
		scanf("%lld %lld %lld", &p, &a, &b);
		printf("%lld\n", (a * b) % p);
	} else puts("0");
}
