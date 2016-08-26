#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef unsigned long long ull;
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
template<typename T> inline T abs(T t) { return t < 0? -t : t; }
const ll modn = 1000000000;
inline ll mod(ll x) { return x % modn; }

int gcd(int a, int b) {
	if(b == 0) return a;
	return gcd(b, a % b);
}
int gc[23][23];

ll memo2[23][23];
ll quant(int i, int j) {
	if(i == j) return 0;
	ll &r = memo2[i][j];
	if(r != -1) return r;
	r = 0;
	for(int k = i + 1; k <= j; k++)
		if(gc[i][k] == 1)
			r++;
	r += quant(i + 1, j);
	return r;
}

int n;
ll memo[23][23], p2[500];
ll solve(int l, int r) {
	if(r == n) return 1;
	ll &ans = memo[l][r];
	if(ans != -1) return ans;
	ans = 0;
	for(int i = l; i <= r; i++)
		for(int j = r + 1; j <= n; j++)
			if(gc[i][j] == 1)
				ans = mod(ans + solve(i + 1, j) * p2[quant(i, j) - 1]);
	return ans;
}

int main() {
	memset(memo, -1, sizeof memo);
	memset(memo2, -1, sizeof memo2);
	p2[0] = 1;
	for(int i = 1; i <= 20; i++)
		for(int j = 1; j <= 20; j++)
			gc[i][j] = gcd(i, j);
	for(int i = 1; i <= 450; i++)
		p2[i] = mod(p2[i - 1] * 2ll);
	scanf("%d", &n);
	if(n == 1) { puts("0"); return 0; }
	printf("%d\n", (int) solve(1, 1));
}
