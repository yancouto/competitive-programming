#include <bits/stdc++.h>
using namespace std;
int n;
int t[9], g[9][9];

bool solve(int i, int j) {
	if(i == n * n) {
		for(i = 0; i < n * n; i++) {
			printf("%d", g[i][0]);
			for(j = 1; j < n * n; j++)
				printf(" %d", g[i][j]);
			putchar('\n');
		}
		return true;
	}
	int ni = i, nj = j + 1;
	if(nj == n * n) nj = 0, ni++;
	if(g[i][j]) return solve(ni, nj);
	int s = 0;
	for(int l = 0; l < n * n; l++)
		s |= 1 << g[i][l];
	for(int l = 0; l < n * n; l++)
		s |= 1 << g[l][j];
	for(int k = (i / n) * n; (k / n) == (i / n); k++)
		for(int l = (j / n) * n; (l / n) == (j / n); l++)
			s |= 1 << g[k][l];
	for(int k = 1; k <= n * n; k++) {
		if(s & (1 << k)) continue;
		g[i][j] = k;
		if(solve(ni, nj))
			return true;
	}
	g[i][j] = 0;
	return false;
}

int main() {
	int i, j; bool f = false;
	while(scanf("%d", &n) != EOF) {
		if(f) putchar('\n');
		f = true;
		for(i = 0; i < n*n ; i++)
			for(j = 0; j < n*n; j++)
				scanf("%d", &g[i][j]);
		if(!solve(0, 0)) puts("NO SOLUTION");
	}
}
