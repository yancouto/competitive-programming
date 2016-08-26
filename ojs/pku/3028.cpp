#include <cstdio>
#include <algorithm>
using namespace std;
#define fst first
#define snd second
typedef pair<int, int> pii;
typedef unsigned long long ull;
typedef long long ll;
typedef long double ld;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
template<typename T> inline T abs(T t) { return t < 0? -t : t; }
const ull modn = 1000000007;
inline ull mod(ull x) { return x % modn; }

int n;
ld p[20];
ld eps = 1e-6;
ld memo[14][14][1 << 14];
ld solve(int ind, int t, int bm) {
	if(!((1 << ind) & bm)) return 0;
	if((bm & (bm - 1)) == 0) return 1;
	ld &r = memo[ind][t][bm];
	if(r > -.5) return r;
	if(r > -1.5) return 0;
	r = -1;
	ld ans = 0, anst = -1; int num = 0, j;
	for(int i = 0; i < n; i++) {
		if(!((1 << i) & bm)) continue;
		if(i == t) continue;
		int nbm = bm ^ (1 << i);
		for(j = t + 1; !(nbm & (1 << (j%n))); j++);
		ld at = solve(t, j%n, nbm);
		if(at > anst + eps) {
			anst = at;
			ans = solve(ind, j%n, nbm);
			num = 1;
		} else if(at >= anst - eps && at <= anst + eps) {
			ans += solve(ind, j%n, nbm);
			num++;
		}
	}
	for(j = t + 1; !(bm & (1 << (j%n))); j++);
	ld allmiss = 1;
	for(int i = 0; i < n; i++)
		if(bm & (1 << i))
			allmiss *= (1 - p[i]);
	ans = p[t] * (ans / num) / (1 - allmiss) + (1 - p[t]) * solve(ind, j%n, bm);
	//printf("ans %Lf\n", ans);
	//printf("allmiss %Lf\n", allmiss);
	r = ans;
	return r;
}

int main() {
	int i, j, k, x;
	for_tests(t, tt) {
		scanf("%d", &n);
		for(i = 0; i < n; i++) {
			scanf("%d", &x);
			p[i] = x / 100.;
			for(j = 0; j < n; j++)
				for(k = 0; k < (1 << n); k++)
					memo[i][j][k] = -2;
		}
		for(i = 0; i < n; i++)
			printf("%.2Lf ", 100*solve(i, 0, (1 << n) - 1));
		printf("\n");
	}
	return 0;
}
