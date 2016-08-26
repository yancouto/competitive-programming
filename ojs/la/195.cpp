#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef pair<int, int> pii;
typedef unsigned long long ull;
typedef long long ll;
typedef double ld;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
template<typename T> inline T abs(T t) { return t < 0? -t : t; }
const ull modn = 1000000007;
inline ull mod(ull x) { return x % modn; }
int n, fR, fK, fKR, d;

ld memo[102][102][102];
ld solve(int i, int r, int k) {
	if(i == d) return (r == 2 * k);
	ld &ret = memo[i][r][k];
	if(ret > -.5) return ret;
	ld dn = n; ret = 0;
	ret += (fR / dn) * solve(i + 1, r + 1, k);
	ret += (fK / dn) * solve(i + 1, r, k + 1);
	ret += (fKR / dn) * solve(i + 1, r + 1, k + 1);
	ret += ((n - fR - fK - fKR) / dn) * solve(i + 1, r, k);
	return ret;
}

int a[40];
int main() {
	int i, j, k, s, x, t = 0;
	while(true) {
		scanf("%d", &n);
		if(!n) return 0;
		scanf("%d", &s);
		memset(a, 0, sizeof a);
		for(i = 0; i < s; i++) {
			scanf("%d", &x);
			a[x] = 1;
		}
		fK = s; fR = 0; fKR = 0;
		scanf("%d", &s);
		for(i = 0; i < s; i++) {
			scanf("%d", &x);
			if(!a[x]) fR++;
			else fK--, fKR++;
		}
		scanf("%d", &d);
		for(i = 0; i < d + 1; i++)
			for(j = 0; j < d + 1; j++)
				for(k = 0; k < d + 1; k++)
					memo[i][j][k] = -1;
		ld dd = solve(0, 0, 0);
		if(dd < 1e-6) printf("Case %d: 0.00000\n", ++t);
		else printf("Case %d: %.5f\n", ++t, dd);
	}
}
