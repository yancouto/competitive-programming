#include <bits/stdc++.h>
using namespace std;

char g[112][112];

int main() {
	freopen("cowsignal.in", "r", stdin);
	freopen("cowsignal.out", "w", stdout);
	int i, j, n, m, k;
	scanf("%d %d %d", &n, &m, &k);
	for(i = 0; i < n; i++)
		for(j = 0; j < m; j++)
			scanf(" %c", &g[i][j]);
	for(i = 0; i < k * n; i++) {
		for(j = 0; j < k * m; j++)
			putchar(g[i / k][j / k]);
		putchar('\n');
	}
}
