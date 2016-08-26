#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef unsigned long long ull;
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }
#ifdef ONLINE_JUDGE
#	define lld I64d
#	define debug(args...) {}
#else
#	define debug(args...) fprintf(stderr, args)
#endif
typedef long double ld;

ld f[100][100], sum[100];
int main() {
	int i, j, n, k;
	scanf("%d %d", &n, &k);
	double x;
	for(i = 0; i < n; i++) scanf("%lf", &x), sum[i] = f[i][1] = x;
	for(j = 2; j <= k; j++) {
		for(i = 0; i < n; i++) {
			ld up = 0, down = 0;
			for(int g = 0; g < n; g++) {
				if(g == i) continue;
				for(int l = 1; l < j; l++)
					down += f[g][1] * f[g][l] / (1. - f[i][l]);
				up += f[g][1] * (1. - sum[g]) / (1. - f[g][j - 1]);
			}
			f[i][j] = f[i][j - 1] * up / (1. - down);
		}
		for(i = 0; i < n; i++)
			sum[i] += f[i][j];
		printf("[%d] ", j);
		for(i = 0; i < n; i++) printf("%.10f ", (double)sum[i]);
		putchar('\n');
	}
	for(i = 0; i < n; i++) printf("%.10f ", (double)sum[i]);
	putchar('\n');
}
