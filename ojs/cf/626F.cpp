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
const int N = 202;

int R[N];
ll c[N][N];
ll comb(int n, int p) {
	if(n < 0 || p > n || p < 0) return 0;
	if(n == 0) return 1;
	ll &r = c[n][p];
	if(r != -1) return r;
	return r = mod(comb(n - 1, p) + comb(n - 1, p - 1));
}

ll solve(int, int, int);
ll memo2[N][N];
ll get(int i, int lock) {
	ll &ans = memo2[i][lock];
	if(ans != -1) return ans;
	ans = 0;
	for(int j = lock; j <= R[i] - i; j++) {
		printf("get(%d, %d) locking %d\n", i, lock, j);
		ans += mod(solve(i + 1, R[i], j) * comb(j, j - lock));
	}
	return ans = mod(ans);
}

ll memo[N][N][N]; int n;
ll solve(int i, int r, int lock) {
	//printf("PD(%d, %d, %d)\n", i, r, lock);
	if(i == n) return lock == 0;
	ll &ans = memo[i][r][lock];
	if(ans != -1) return ans;
	ans = 0;
	if(lock > r - i + 1) return ans = 0;
	if(i <= r && lock) ans = solve(i + 1, r, lock - 1);
	if(i > r || lock != r - i + 1) ans += get(i, lock);
	printf("solve(%d, %d, %d) = %lld\n", i, r, lock, ans);
	return ans = mod(ans);
}

int a[N];
int main() {
	int i, k;
	scanf("%d %d", &n, &k);
	for(i = 0; i < n; i++)
		scanf("%d", &a[i]);
	sort(a, a + n);
	int r = 0;
	for(i = 0; i < n; i++) {
		for(; r < n && a[r] - a[i] <= k; r++);
		R[i] = r - 1;
		printf("%d->%d\n", i, R[i]);
	}
	memset(memo, -1, sizeof memo);
	memset(memo2, -1, sizeof memo2);
	memset(c, -1, sizeof c);
	printf("%d\n", (int) solve(0, 0, 0));
}
