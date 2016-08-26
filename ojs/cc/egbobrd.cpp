#include <cstdio>
typedef unsigned long long ull;
const int MAX = 100009;
int n;
ull k;

ull solve() {
	int i, x;
	ull spent = 1, left = k;
	for(i = 0; i < n; i++) {
		scanf("%d", &x);
		if(x <= left)
			left -= x;
		else {
			x -= left;
			int sp = (x + k - 1) / k;
			spent += sp;
			left = k - (x - (sp - 1) * k);
		}
		if(left) left--;
	}
	return spent;
}


int main() {
	int t, i;
	scanf("%d", &t);
	while(t--) {
		scanf("%d %llu", &n, &k);
		printf("%llu\n", solve());
	}
	return 0;
}