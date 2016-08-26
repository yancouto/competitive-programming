#include <bits/stdc++.h>
using namespace std;

int a[22];
int main() {
	int i, j, n;
	scanf("%d", &n);
	for(i = 0; i < n; i++)
		scanf("%d", &a[i]);
	int mn = 1000000;
	for(i = 0; i < (1 << n); i++) {
		int w[2] = {0, 0};
		for(j = 0; j < n; j++)
			w[!!(i & (1 << j))] += a[j];
		mn = min(mn, abs(w[0] - w[1]));
	}
	printf("%d\n", mn);
}
