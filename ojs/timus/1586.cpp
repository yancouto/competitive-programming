#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll modn = 1000000009;
inline ll mod(ll x) { return x % modn; }
int pr[10009], n;
ll memo[10002][10][10][2];
ll solve(int d, int l2, int l1, bool ok) {
	if(d == n) return ok;
	ll &r = memo[d][l2][l1][ok];
	if(r != -1) return r;
	r = 0;
	for(int i = 0; i <= 9; i++)
		r = mod(r + solve(d + 1, l1, i, ok && (d < 2 || pr[l2 * 100 + l1 * 10 + i])));
	return r;
}

int main() {
	int i, j;
	scanf("%d", &n);
	for(i = 100; i < 1000; i++) {
		for(j = 2; j * j <= i; j++)
			if(!(i % j))
				break;
		if(j * j > i) pr[i] = 1;
	}
	memset(memo, -1, sizeof memo);
	printf("%lld\n", solve(0, 0, 0, true));
}
