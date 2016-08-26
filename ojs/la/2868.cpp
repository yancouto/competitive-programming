#include <cstdio>
int n, m;
int mat[1003][1003];

int get_sum(int x1, int y1, int x2, int y2) {
	return mat[x2][y2] - mat[x1 - 1][y2] - mat[x2][y1 - 1] + mat[x1 - 1][y1 - 1];
}

int main() {
	int i, j;
	while(true) {
		scanf("%d %d", &n, &m);
		if(!n) return 0;
		for(i = 1; i <= n; i++)
			for(j = 1; j <= m; j++) {
				scanf("%d", &mat[i][j]);
				mat[i][j] += mat[i][j - 1];
			}
		for(j = 1; j <= m; j++)
			for(i = 1; i <= n; i++)
				mat[i][j] += mat[i - 1][j];

		int k = 0;
		for(i = 1; i <= n; i++)
			for(j = 1; j <= m; j++)
				for(int k2 = k + 1; i - k2 + 1 > 0 && j - k2 + 1 > 0 && get_sum(i - k2 + 1, j - k2 + 1, i, j) == k2 * k2; k2++)
					k = k2;
		printf("%d\n", k);
	}
}