#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)

ll inf = 1e15;
const int N = 112;
ll d[N][N];
double D[N][N];
int seen[N], e[N], s[N];

int main() {
	int i, j, k, n, q;
	for_tests(tn, tt) {
		scanf("%d %d", &n, &q);
		for(i = 0; i < n; i++) scanf("%d %d", &e[i], &s[i]);
		for(i = 0; i < n; i++)
			for(j = 0; j < n; j++) {
				scanf("%lld", &d[i][j]);
				if(d[i][j] == -1) d[i][j] = inf;
			}
		for(i = 0; i < n; i++) d[i][i] = 0;
		for(k = 0; k < n; k++)
			for(i = 0; i < n; i++)
				for(j = 0; j < n; j++)
					d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
		//for(i = 0; i < n; i++)
		//	for(j = 0; j < n; j++)
		//		printf("%lld%c", d[i][j], " \n"[j == n - 1]);
		for(i = 0; i < n; i++) {
			// dijkstra
			for(j = 0; j < n; j++) D[i][j] = 1. / 0., seen[j] = 0;
			D[i][i] = 0;
			while(true) {
				int nx = -1;
				for(j = 0; j < n; j++)
					if(!seen[j] && D[i][j] != 1./0. && (nx == -1 || D[i][j] < D[i][nx]))
						nx = j;
				if(nx == -1) break;
				//printf("D[%d][%d] = %.10f\n", i, nx, D[i][nx]);
				seen[nx] = 1;
				for(j = 0; j < n; j++) {
					if(d[nx][j] > e[nx]) continue;
					D[i][j] = min(D[i][j], D[i][nx] + double(d[nx][j]) / double(s[nx]));
				}
			}
		}
		printf("Case #%d:", tt);
		for(i = 0; i < q; i++) {
			int a, b;
			scanf("%d %d", &a, &b); a--; b--;
			printf(" %.12f", D[a][b]);
		}
		putchar('\n');
	}
}
