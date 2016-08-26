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
const ll modn = 998244353ll;
inline ll mod(ll x) { return x % modn; }
const int N = 1123;
ll p[N];
int ans[N];

int solve(int n) {
	ll tot = 0;
	for(int i = 1; i <= n; i++) {
		int x = n % i;
		if(x == 0) x = i;
		tot += p[x];
	}
	return (int) mod(tot);
}

int main() {
	freopen("cover.in", "r", stdin);
	freopen("cover.out", "w", stdout);
	int i, n;
	p[0] = 1;
	for(i = 1; i < N; i++)
		p[i] = mod(p[i - 1] * 2ll);
	for(i = 1; i <= 1000; i++)
		ans[i] = solve(i);
	while(scanf("%d", &n) != EOF && n)
		printf("%d\n", ans[n]);
}
