#include <cstdio>
typedef unsigned long long ull;

int main() {
	int n, i, x, y, n5;
	scanf("%d", &n);
	for(i = 0; i < n; i++) {
		scanf("%d", &x);
		y = x;
		while((y % 10) == 0)
			y /= 10;
		for(n5 = 0; (y % 5) == 0; n5++)
			y /= 5;
		n5 = (n5 + 1) / 2;
		ull xx = x;
		while(n5--)
			xx <<= 2;
		printf("%llu\n", xx);
	}
	return 0;
}