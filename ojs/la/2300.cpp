#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }

int r;
double memo[112][10009][31];
int seen[112][10009][31], tempo;
double solve(int n, int money, int R) {
	if(n == 0) return 1;
	double &r = memo[n][money][R];
	if(seen[n][money][R] == tempo) return r;
	seen[n][money][R] = tempo;
	r = 0;
	for(int i = 1; i <= R && i <= money; i++)
		r += (1. / R) * solve(n - 1, money - i, R);
	return r;
}

int d[112][112];

int main() {
	int i, j, n, k, m, a, b; char c;
	tempo++;
	for_tests(tn, tt) {
		scanf("%d %d", &n, &r);
		for(i = 0; i < n; i++)
			for(j = 0; j < n; j++) {
				scanf(" %c", &c);
				d[i][j] = (c == 'Y'? 1 : 1e8);
				if(i == j) d[i][i] = 0;
			}
		for(k = 0; k < n; k++)
			for(i = 0; i < n; i++)
				for(j = 0; j < n; j++)
					d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
		printf("Case %d\n", tt);
		for_tests(qn, qq) {
			scanf("%d %d %d", &a, &b, &m); a--; b--;
			printf("%.10f\n", solve(d[a][b], m, r));
		}
		putchar('\n');
	}
}
