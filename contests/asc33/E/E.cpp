#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 190;
ll memo[N][N], memo2[N][N][N], memo3[N][N];
int seen[N][N], seen2[N][N][N], seen3[N][N];

ll ch(int n, int p) {
	if(p > n || p < 0) return 0;
	if(n == 0) return 1;
	ll &r = memo3[n][p];
	if(seen3[n][p]) return r;
	seen3[n][p] = 1;
	return r = ch(n - 1, p) + ch(n - 1, p - 1);
}

ll pd(int, int);

ll choose(int n, int sz, int left) {
	if(left == 0) return n == 0;
	if(left > sz) return 0;
	ll &r = memo2[n][sz][left];
	if(seen2[n][sz][left]) return r;
	seen2[n][sz][left] = 1;
	r = 0;
	for(int x = 1; x <= n; x++)
		r += ch(n - 1, x - 1) * choose(n - x, sz, left - 1) * pd(x - 1, sz);
	//printf("choose(%d, %d, %d) = %lld\n", n, sz, left, r);
	return r;
}

ll pd(int n, int mx) {
	if(n == 0) return 1;
	ll &r = memo[n][mx];
	if(seen[n][mx]) return r;
	seen[n][mx] = 1;
	r = 0;
	for(int sz = 1; sz <= mx; sz++)
		r += choose(n, sz, sz);
	//printf("pd(%d, %d) = %lld\n", n, mx, r);
	return r;
}

int main() {
	int n;
	scanf("%d", &n);
	printf("%d\n", pd(n - 1, n - 1));
}
