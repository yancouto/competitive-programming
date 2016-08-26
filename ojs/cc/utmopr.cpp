#include <cstdio>

int main() {
	int t;
	scanf("%d", &t);
	while(t--) {
		int odds = 0;
		int n, k, x;
		scanf("%d %d", &n, &k);
		for(int i = 0; i < n; i++) {
			scanf("%d", &x);
			if(x & 1) odds = !odds;
		}
		if(k == 1 && odds == 0) puts("odd");
		else puts("even");
	}
	return 0;
}