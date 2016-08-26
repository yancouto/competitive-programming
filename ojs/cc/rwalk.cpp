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

int a[1000], b[1000];

int sn, sum;
int memo[2][253*509];
//int seen[254][253*253], t;
inline int solve(int i, int x) {
	if(2*x > sum) return INT_MAX;
	if(i == sn) return sum - 2*x;
	return memo[i & 1][x];
	//int &r = memo[i][x];
	//if(seen[i][x] == t) return r;
	//seen[i][x] = t;
	//r = solve(i + 1, x);
	//if(2*(x + a[i]) <= sum) r = min(r, solve(i + 1, x + a[i]));
	//return r;
}

int main() {
	int i, n, x;
	for_tests(tn, tt) {
		scanf("%d", &n);
		for(i = 0; i < 2*n + 1; i++)
			if(i & 1) scanf(" %*c");
			else scanf("%d", &b[i/2]);
		if(n <= 2) { puts("NO"); continue; }
		n++; sn = sum = 0;
		for(i = 0; i < n; i += 2)
			a[sn++] = b[i], sum += b[i];
		for(i = sn - 1; i >= 0; i--)
			for(x = 0; 2*x <= sum; x++)
				memo[i & 1][x] = min(solve(i + 1, x), solve(i + 1, x + a[i]));
		int tot = solve(0, 0);
		sn = sum = 0;
		for(i = 1; i < n; i += 2)
			a[sn++] = b[i], sum += b[i];
		for(i = sn - 1; i >= 0; i--)
			for(x = 0; 2*x <= sum; x++)
				memo[i & 1][x] = min(solve(i + 1, x), solve(i + 1, x + a[i]));
		tot += solve(0, 0);
		printf("%d\n", tot);
	}
}
