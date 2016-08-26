#include <bits/stdc++.h>
using namespace std;

int main() {
	int i, j, n, m, x;
	scanf("%d %d", &n, &m);
	int tot = 0;
	for(i = 0; i < n; i++) {
		int mn = INT_MAX;
		for(j = 0; j < m; j++) {
			scanf("%d", &x);
			mn = min(mn, x);
		}
		if(mn) tot++;
	}
	printf("%d\n", tot);
	return 0;
}
