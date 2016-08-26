#include <cstdio>

int main() {
	int t;
	scanf("%d", &t);
	while(t--) {
		int n, i, x;
		scanf("%d", &n);
		bool all_1 = true;
		int num = 0;
		for(i = 0; i < n; i++) {
			scanf("%d", &x);
			num ^= x;
			if(x != 1) all_1 = false;
		}
		if(all_1) num = !(n % 2); 
		if(num) puts("John");
		else puts("Brother");
	}
	return 0;
}