#include <bits/stdc++.h>
using namespace std;

int a[125001];
int main() {
	int i, n, x;
	scanf("%d", &n);
	for(i = 0; i <= n / 2; i++)
		scanf("%d", &a[i]);
	make_heap(a, a + (n/2) + 1);
	for(i = (n/2) + 1; i < n; i++) {
		scanf("%d", &x);
		if(x > a[0]) continue;
		pop_heap(a, a + (n/2) + 1);
		a[(n/2)] = x;
		push_heap(a, a + (n/2) + 1);
	}
	int aa = a[0];
	pop_heap(a, a + (n/2) + 1);
	int bb = a[0];
	if(n & 1) bb = aa;
	printf("%.1f\n", aa + (bb - aa) / 2.);
	return 0;
}
