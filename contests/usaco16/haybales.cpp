#include <bits/stdc++.h>
using namespace std;

int a[112345];

int main() {
	freopen("haybales.in", "r", stdin);
	freopen("haybales.out", "w", stdout);
	int i, n, q, l, r;
	scanf("%d %d", &n, &q);
	for(i = 0; i < n; i++)
		scanf("%d", &a[i]);
	sort(a, a + n);
	for(i = 0; i < q; i++) {
		scanf("%d %d", &l, &r);
		printf("%d\n", upper_bound(a, a + n, r) - lower_bound(a, a + n, l));
	}
}
