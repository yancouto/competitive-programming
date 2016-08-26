#include <bits/stdc++.h>
using namespace std;

int main() {
	int k, n, a[1022], i, x;
	scanf("%d %d", &k, &n);
	int cur = 0;
	for(i = 0; i < n; i++) {
		scanf("%d", &x);
		cur = max(cur + x - k, 0);
	}
	printf("%d\n", cur);
}
