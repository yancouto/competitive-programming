#include <cstdio>
typedef unsigned long long ull;
const ull modn = 1000000007;
inline ull mod(ull x) { return x % modn; }

ull get2(ull n) {
	return mod((n * (n - 1)) / 2);
}

ull get22(ull n) {
	return mod(n * (n - 1));
}

ull solve_2(int, int);

ull memo1[100009][53];
ull solve_full(int n, int k) {
	if(n < 0) return 0;
	if(n == 1) return 0;
	if(n == 0) return k == 0;
	if(k == 0) return 0;
	ull &m = memo1[n][k];
	if(m) return m - 1;
	ull x = mod(solve_full(n - 2, k - 1) * mod(get2(n) * (n - 1)));
	x = mod(x + mod(solve_2(n, k) * mod(get2(n) * get22(n - 1))));
	m = x + 1;
	return x;
}

ull memo2[100009][53];
ull solve_2(int n, int k) {
	ull &m = memo2[n][k];
	if(m) return m - 1;
	ull x = mod(solve_full(n - 3, k - 1) * (n - 2));
	if(n > 3)
		x = mod(x + mod(solve_2(n - 1, k) * get22(n - 2)));
	m = x + 1;
	return x;
}

int main() {
	int t, i;
	scanf("%d", &t);
	for(int tt = 1; tt <= t; tt++) {
		int n, k;
		scanf("%d %d", &n, &k);
		printf("Case %d: %d\n", tt, (int) solve_full(n, k));
	}
	return 0;
}