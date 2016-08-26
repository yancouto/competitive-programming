#include <bits/stdc++.h>
using namespace std;

int a[100][100];

int main() {
	int n, i, j, k;
	scanf("%d", &n);
	for(i = 0; i < n; i++)
		for(j = 0; j < n; j++)
			scanf("%d", &a[i][j]);
	for(k = 0; k < n; k++)
		for(i = 0; i < n; i++)
			for(j = 0; j < n; j++)
				a[i][j] = min(a[i][j], a[i][k] + a[k][j]);
	int m = 0;
	for(i = 0; i < n; i++)
		for(j = 0; j < n; j++)
			m = max(m, a[i][j]);
	printf("%d\n", m);
}
