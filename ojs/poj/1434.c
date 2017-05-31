#include <stdio.h>
int hs[1040009];

void solve() {
	int v, ac = 0, i;
	int tot = 0; int last = 0;
	scanf("%d", &v);
	for(i = 0; i < 1040009; i++) {
		int cur = tot + ac;
		if(cur >= v) {
			printf("%.2lf\n", (i - 1 + ((double) (v - tot)) / ac));
			return;
		}
		ac += hs[i];
		tot = cur;
	}
	puts("OVERFLOW");
}
int acs[100009];

int main() {
	int t, i, j;
	scanf("%d", &t);
	while(t--) {
		int n, b, h, w, d;
		scanf("%d", &n); j = 0;
		for(i = 0; i < n; i++) {
			scanf("%d %d %d %d", &b, &h, &w, &d); d *= w;
			hs[b] += d;
			hs[b + h] -= d;
			acs[j++] = b;
			acs[j++] = b + h;
		}
		solve();
		for(i = 0; i < 2 * n; i++)
			hs[acs[i]] = 0;
	}
	return 0;
}