#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)

char g[112][112];

int main() {
	int i, j, n, m, k;
	for_tests(t, tt) {
		scanf("%d %d", &n, &m);
		for(i = 0; i < n; i++)
			for(j = 0; j < m; j++)
				scanf(" %c", &g[i][j]);
		for(i = 0; i < n; i++) g[i][m] = 0;
		int ct = 0;
		for(i = 0; i < n; i++)
			for(j = 0; j < m; j++)
				ct += (g[i][j] == '?');
		fprintf(stderr, "%d %d\n", n, m);
		for(i = 0; i < n; i++)
			for(j = 0; j < m; j++)
				fprintf(stderr, "%c%c", g[i][j], " \n"[j == m - 1]);
		while(ct > 0) {
			fprintf(stderr, "ct %d\n", ct);
			for(i = 0; i < n; i++)
				for(j = 0; j < m; j++)
					fprintf(stderr, "%c%c", g[i][j], " \n"[j == m - 1]);
			for(i = 0; i < n; i++)
				for(j = 0; j < m; j++) {
					if((i && g[i - 1][j] == g[i][j]) || (j && g[i][j - 1] == g[i][j])) continue;
					for(k = j; k < m && g[i][k] == g[i][j] && i && g[i - 1][k] == '?'; k++);
					if(k == m || g[i][k] != g[i][j]) {
						for(k = j; k < m && g[i][k] == g[i][j]; k++)
							g[i - 1][k] = g[i][j], ct--;
						break;
					}
					for(k = i; k < n && g[k][j] == g[i][j] && j && g[k][j - 1] == '?'; k++);
					if(k == n || g[k][j] != g[i][j]) {
						for(k = i; k < n && g[k][j] == g[i][j]; k++)
							g[k][j - 1] = g[i][j], ct--;
						break;
					}
					int pi = i, pj = j;
					while(i + 1 < n && g[i + 1][j] == g[i][j]) i++;
					while(j + 1 < m && g[i][j + 1] == g[i][j]) j++;
					for(k = j; k >= 0 && g[i][k] == g[i][j] && i < n && g[i + 1][k] == '?'; k--);
					if(k < 0 || g[i][k] != g[i][j]) {
						for(k = j; k >= 0 && g[i][k] == g[i][j]; k--)
							g[i + 1][k] = g[i][j], ct--;
						break;
					}
					for(k = i; k >= 0 && g[k][j] == g[i][j] && j < m && g[k][j + 1] == '?'; k--);
					if(k < 0 || g[k][j] != g[i][j]) {
						for(k = i; k >= 0 && g[k][j] == g[i][j]; k--)
							g[k][j + 1] = g[i][j], ct--;
						break;
					}
					i = pi; j = pj;
				}
		}
		printf("Case #%d:\n", tt);
		for(i = 0; i < n; i++)
			puts(g[i]);
	}
}
