#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef pair<int, int> pii;
typedef unsigned long long ull;
typedef long double ld;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
template<typename T> inline T abs(T t) { return t < 0? -t : t; }
#ifndef ONLINE_JUDGE
#	define debug(args...) {fprintf(stderr, "%3d| ", __LINE__); fprintf(stderr, args); fprintf(stderr, "\n");}
#else
#	define debug(args...) {}
#endif
const ull modn = 1000000007;
inline ull mod(ull x) { return x % modn; }
int n, t, ts[53], rr[52][209], ll[52][209];
const int inf = 1000000;
int memo[52][209];
int solve(int i, int tim) {
	if(tim > t) return inf;
	if(i == n - 1 && tim == t) return 0;
	int &r = memo[i][tim];
	if(r != -1) return r;
	r = solve(i, tim + 1) + 1;
	if(rr[i][tim]) r = min(r, solve(i + 1, tim + ts[i]));
	if(ll[i][tim]) r = min(r, solve(i - 1, tim + ts[i - 1]));
	return r;
}

int main() {
	int cn = 0, i, j, x, m;
	while(true) {
		scanf("%d", &n);
		if(!n) return 0;
		scanf("%d", &t);
		for(i = 0; i < n - 1; i++)
			scanf("%d", &ts[i]);
		scanf("%d", &m);
		memset(rr, 0, sizeof rr);
		memset(ll, 0, sizeof ll);
		for(i = 0; i < m; i++) {
			scanf("%d", &x); 
			int d = 1, st = 0;
			while(x <= 200) {
				((d == 1)? rr : ll)[st][x] = 1;
				x += ts[st - (d < 0)];
				st += d;
				if(st == n - 1 || st == 0) break;
			}
		}
		scanf("%d", &m);
		for(i = 0; i < m; i++) {
			scanf("%d", &x);
			int d = -1, st = n - 1;
			while(x <= 200) {
				((d == 1)? rr : ll)[st][x] = 1;
				x += ts[st - (d < 0)];
				st += d;
				if(st == n - 1 || st == 0) break;
			}
		}
		memset(memo, -1, sizeof memo);
		int a = solve(0, 0);
		printf("Case Number %d: ", ++cn);
		if(a >= inf) puts("impossible");
		else printf("%d\n", a);
	}
}
