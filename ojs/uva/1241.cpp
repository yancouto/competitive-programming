#include <bits/stdc++.h>
using namespace std;

int main() {
	int i, t, f, a, b, c, j;
	scanf("%d", &t);
	for(i = 0; i < t; i++) {
		scanf("%d", &f);
		long long val = 0;
		for(j = 0; j < f; j++) {
			scanf("%d %d %d", &a, &b, &c);
			val += ((long long) a) * c;
		}
		printf("%lld\n", val);
	}
	return 0;
}
