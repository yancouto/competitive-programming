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

int n, k, t1, t2;
int memo[52][52][206][2];
int solve(int l1, int l2, int tim, bool left) {
	if(l1 == 0 && l2 == 0) return tim;
	if(tim > 202) return INT_MAX;
	int &r = memo[l1][l2][tim][left];
	if(r != -1) return r;
	r = INT_MAX;
	int r1 = t1 - l1, r2 = t2 - l2;
	if(left) {
		for(int i = 0; i <= l2 && i * 2 <= k; i++)
			r = min(r, solve(max(0, l1 - (k - i * 2)), l2 - i, tim + 1, false));
	} else {
		if(r1) r = min(r, solve(l1 + 1, l2, tim + 1, true));
		if(r2) r = min(r, solve(l1, l2 + 1, tim + 1, true));
	}
	return r;
}

ll c[52][52];
ll comb(int p, int n) {
	if(p > n || p < 0) return 0;
	if(n == 0) return 1;
	ll &r = c[p][n];
	if(r != -1) return r;
	return r = mod(comb(p - 1, n - 1) + comb(p, n - 1));
}

ll memo2[52][52][206][2];
ll solve2(int l1, int l2, int mvs, bool left) {
	if(mvs == 0) return l1 == 0 && l2 == 0;
	ll &r = memo2[l1][l2][mvs][left];
	if(r != -1) return r;
	r = 0;
	int r1 = t1 - l1, r2 = t2 - l2;
	if(left) {
		for(int i = 0; i <= l2 && i * 2 <= k; i++)
			for(int j = 0; j <= l1 && i * 2 + j <= k; j++)
				if(i || j)
					r += mod(mod(comb(j, l1) * comb(i, l2)) * solve2(l1 - j, l2 - i, mvs - 1, false));
	} else {
		for(int i = 0; i <= r2 && i * 2 <= k; i++)
			for(int j = 0; j <= r1 && i * 2 + j <= k; j++)
				if(i || j)
					r += mod(mod(comb(j, r1) * comb(i, r2)) * solve2(l1 + j, l2 + i, mvs - 1, true));
	}
	return r = mod(r);
}

int main() {
	memset(c, -1, sizeof c);
	scanf("%d %d", &n, &k);
	int i, x;
	k /= 50;
	for(i = 0; i < n; i++) {
		scanf("%d", &x);
		if(x == 50) t1++;
		else t2++;
	}
	if(n == 1) {
		if(k >= 2 || (k == 1 && t1)) printf("1\n1\n");
		else printf("-1\n0\n");
		return 0;
	}
	memset(memo, -1, sizeof memo);
	memset(memo2, -1, sizeof memo2);
	int r = solve(t1, t2, 0, true);
	if(r == INT_MAX) printf("-1\n0\n");
	else printf("%d\n%d\n", r, int(solve2(t1, t2, r, true)));
}
