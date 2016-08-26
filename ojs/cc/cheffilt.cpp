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
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }

int read() {
	char c;
	while(isspace(c = getchar()));
	ungetc(c, stdin);
	int num = 0;
	for(int i = 0; i < 10; i++)
		num |= ((c = getchar()) == '+' || c == 'w') << i;
	return num;
}

ll fexp(ll x, ll p) {
	ll res = 1;
	for(; p; p >>= 1) {
		if(p & 1) res = mod(res * x);
		x = mod(x * x);
	}
	return res;
}

ll fat[100009];
ll comb(ll n, ll p) {
	return mod(fat[n] * fexp(mod(fat[p] * fat[n - p]), modn - 2));
}

ll calc(int n, int st) {
	ll tot = 0;
	for(; st <= n; st += 2)
		tot += comb(n, st);
	return mod(tot);
}

ll dp[2][1024];
int f[1024]; ll fo[1024], fe[1024];
int main() {
	int i, n, j;
	fat[0] = 1;
	for(i = 1; i < 100009; i++)
		fat[i] = mod(fat[i - 1] * ll(i));
	for_tests(t, tt) {
		int b = read();
		scanf("%d", &n);
		memset(f, 0, sizeof f);
		for(i = 0; i < n; i++)
			f[read()]++;
		for(i = 0; i < 1024; i++)
			fo[i] = calc(f[i], 1),
			fe[i] = calc(f[i], 0);
		memset(dp, 0, sizeof dp);
		dp[1024&1][0] = 1;
		for(i = 1023; i >= 0; i--)
			for(j = 0; j < 1024; j++)
				dp[i&1][j] = mod(fe[i] * dp[!(i&1)][j] + fo[i] * dp[!(i&1)][j ^ i]);
		printf("%d\n", (int) dp[0][b]);
	}
}
