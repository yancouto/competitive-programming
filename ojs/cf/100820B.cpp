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
#	define LLD "%I64d"
#	define debug(args...) {}
#else
#	define LLD "%lld"
#	define debug(args...) fprintf(stderr, args)
#endif

double mx[1009], mn[1009];
int b[30];
int p[30][30], q[30][30];

int n, m;
int memo2[20][1 << 19];
int seen[20][1 << 19];
int calc(int i, int bm) {
	if(seen[i][bm]) return memo2[i][bm];
	int B = b[i];
	for(int j = 0; j < i; j++)
		if((bm >> j) & 1)
			B += p[j][i];
		else B += q[j][i];
	B = -B + 1;
	if(B < 1) B = 1;
	if(B > m) B = m + 1;
	return memo2[i][bm] = B;
}

double memo[2][21][1 << 19];
double solve(int i, int k, int bm) {
	if(i == n) return (bm >> (n - 1)) & 1;
	return memo[i & 1][k][bm];
}

int main() {
	int i, j, K, k, bm;
	scanf("%d %d %d", &n, &K, &m);
	for(i = 1; i <= m; i++)
		for(j = 1; j <= m; j++)
			mx[max(i, j)]++, mn[min(i, j)]++;
	for(i = m - 1; i > 0; i--) mx[i] += mx[i + 1];
	for(i = 2; i <= m; i++) mn[i] += mn[i - 1];
	for(i = 1; i <= m; i++) mx[i] /= (m * m), mn[i] /= (m * m);
	for(i = 0; i < n; i++) {
		scanf("%d", &b[i]);
		for(j = i + 1; j < n; j++)
			scanf("%d", &p[i][j]);
		for(j = i + 1; j < n; j++)
			scanf("%d", &q[i][j]);
	}
	memset(memo2, -1, sizeof memo2);
	for(i = n - 1; i >= 0; i--) {
		for(k = 0; k <= n - i; k++) {
			for(bm = 0; bm < (1 << i); bm++) {
				double &r = memo[i&1][k][bm];
				int b = calc(i, bm); // precisa >= b
				double pl = double(b - 1) / m; double pw = 1. - pl;
				r = pl * solve(i + 1, k, bm) + pw * solve(i + 1, k, bm | (1 << i));
				if(k) {
					pl = mn[b - 1]; pw = 1. - pl;
					double ans = pl * solve(i + 1, k - 1, bm) + pw * solve(i + 1, k - 1, bm | (1 << i));
					r = max(r, ans);
					pw = mx[b]; pl = 1. - pw;
					ans = pl * solve(i + 1, k - 1, bm) + pw * solve(i + 1, k - 1, bm | (1 << i));
					r = max(r, ans);
				}
			}
		}
	}
	printf("%.6f\n", memo[0][K][0]);
}
