#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }
#ifdef ONLINE_JUDGE
#	define debug(args...) {}
#else
#	define debug(args...) fprintf(stderr, args)
#endif

int n;

double p[12], g[12];
double fat[112];

double memo[22][22];
bool seen[22][22];
double solve(int i, int m) {
	if(i == 0) return m == 0;
	double &r = memo[i][m];
	if(seen[i][m]) return r;
	seen[i][m] = true;
	r = solve(i - 1, m);
	double pr = p[i];
	for(int j = 2; j <= m; j++) {
		pr *= p[i];
		r += (pr / fat[j]) * solve(i - 1, m - j);
	}
	return r;
}
double win[23];

int main() {
	int i, j, m;
	fat[0] = 1;
	for(i = 1; i <= 12; i++)
		fat[i] = i * fat[i - 1];
	scanf("%d %d", &n, &m);
	for(i = 1; i <= m; i++) p[i] = 1. / m;
	int lim = 0;
	while(clock() < CLOCKS_PER_SEC * 1.3) {
		double eps = 1e-5;
		memset(seen, 0, sizeof seen);
		double all = 0;
		for(i = m; i > 0; i--) g[i] = p[i] + g[i + 1];
		for(i = 1; i <= m; i++) {
			win[i] = 0;
			for(j = 0; j < n; j++)
				win[i] += solve(i - 1, j) * (fat[n - 1] / fat[n - 1 - j]) * pow(g[i + 1], n - 1 - j);
		}
		for(i = 1; i <= m; i++) all += win[i];
		for(i = 1; i <= m; i++)
			if(win[i] > all / m)
				p[i] += eps;
			else if(win[i] < all / m)
				p[i] -= eps;
		all = 0;
		for(i = 1; i <= m; i++) all += p[i];
		for(i = 1; i <= m; i++) p[i] = p[i] / all;
	}
	for(i = 1; i <= m; i++) printf("%.10f ", p[i]); putchar('\n');
}
