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

const int N = 223;

ll fexp(ll x, ll p) {
	ll r = 1;
	for(; p; p >>= 1, x = mod(x * x))
		if(p & 1)
			r = mod(x * r);
	return r;
}

inline ll inv(ll x) { return fexp(x, modn - 2); }

ll a[N][N];
ll ans[N];
ll x[N][N];
int t;

// sum(a[i][j] * x_j) = a[i][n] para 0 <= i < n
void solve(int n, ll ans[]) {
	for(int i = 0; i < n; i++) {
		int mx = i;
		for(int j = i + 1; j < n; j++)
			if((a[j][i]) > (a[mx][i]))
				mx = j;
		swap_ranges(a[i], a[i] + n + 1, a[mx]);
		assert(a[i][i]);
		ll aii = inv(a[i][i]);
		for(int j = i + 1; j < n; j++) {
			for(int k = i + 1; k <= n; k++)
				a[j][k] = mod(a[j][k] - mod(mod(a[j][i] * aii) * a[i][k]) + modn);
			a[j][i] = 0;
		}
	}
	for(int i = n - 1; i >= 0; i--) {
		ans[i] = a[i][n];
		for(int j = i + 1; j < n; j++)
			ans[i] = mod(ans[i] - mod(a[i][j] * ans[j]) + modn);
		ans[i] = mod(ans[i] * inv(a[i][i]));
	}
}

void clean(ll ans[]) {
	for(int i = 0; i < n; i++)
		if(ans[i] > modn/2)
			ans[i] -= modn;
}

set<ll> op;
int l[112], r[112], g[112];
void query(ll ans[]) {
	printf("?");
	for(int i = 0; i < n; i++) printf(" %d", g[i]); putchar('\n');
	ll cur = 0;
	for(int i = 0; i < n; i++) cur = mod(cur * 123ll + g[i]);
	assert(!op.count(cur));
	op.insert(cur);
	fflush(stdout);
	for(int i = 0; i < n; i++) scanf("%lld", &ans[i]);
	if(ans[0] == 987654321) exit(0);
	int i;
	for(i = 0; i < n && ans[i] == 0; i++);
	if(i == n) {
		printf("A");
		for(int i = 0; i < n; i++) printf(" %d", g[i]); putchar('\n');
		fflush(stdout);
		exit(0);
	}
}

int mdc(int a, int b) {
	if(b == 0) return a;
	return mdc(b, a % b);
}

int main() {
	int i, j; int m;
	scanf("%d %d", &n, &m);
	for(i = 0; i < n; i++) g[i] = 1;
	query(x[0]);
	for(i = n - 1; i >= 0; i--) {
		g[i]++;
		query(ans);
		for(j = 0; j < n; j++) x[i][j] = ans[j] - x[0][j];
		int gcd = abs(x[i][0]);
		for(j = 1; j < n; j++) gcd = mdc(gcd, abs(x[i][j]));
		for(j = 0; j < n; j++) x[i][j] /= gcd;
		for(j = 0; j < n; j++) x[i][j] = mod(x[i][j] + modn);
		g[i]--;
	}
	for(i = 0; i < n; i++) l[i] = 1, r[i] = m;
	op.clear();
	while(true) {
		for(i = 0; i < n; i++)
			g[i] = (l[i] + r[i]) / 2;
		query(ans);
		for(i = 0; i < n; i++)
			for(j = 0; j < n; j++)
				a[j][i] = x[i][j];
		for(i = 0; i < n; i++)
			a[i][n] = mod(ans[i] + modn);
		solve(n, ans);
		for(i = 0; i < n; i++)
			if(ans[i] < modn / 2)
				r[i] = g[i];
			else
				l[i] = g[i] + 1;
	}
}
