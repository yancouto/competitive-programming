#include <bits/stdc++.h>
using namespace std;

int pi[100009];
int main() {
	int i, j, x, c, n;
	scanf("%d %d", &c, &n);
	for(i = 0; i < n; i++) {
		scanf("%d", &x);
		pi[x] = 1;
	}
	for(i = 1; i < c; i++)
		pi[i] += pi[i - 1];
	for(i = 0; i < (c / n); i++) {
		for(j = 0; j < n - 1; j++)
			if(pi[i + (j + 1) * (c / n) - 1] != pi[i + j * (c / n) - 1] + 1)
				break;
		if(j == n - 1) break;
	}
	if(i < (c / n)) puts("S");
	else puts("N");
	return 0;
}
