#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
int modn = 1000000007;
inline int mod(int x) { return x % modn; }

int n, m;
// cmp = n - bk
//int solve(int i, int rc, int bk) {
//	const int cmp = n - bk;
//	assert(rc >= bk);
//	//if(i < rc || i > (bk + 1) * (rc) + ((rc - bk) * (rc - bk - 1)) / 2) return 0;
//	//if(i == m) printf(">> (%d, %d, %d)\n", i, rc, bk);
//	if(i == m) return 1;
//	int &r = memo[i][rc][bk];
//	if(r != -1) return r;
//	if(rc < n - 1) r = solve(i + 1, rc + 1, bk);
//	else r = solve(i + 1, rc, bk);
//	for(int j = 1; j <= rc - bk; j++)
//		r = mod(r + solve(i + 1, rc, bk + j));
//	//printf("solve(%d, %d, %d) = %d\n", i, rc, bk, r);
//	return r;
//}

inline bool valid(int e, int rc, int bk, int iv) {
	if(bk >= n || rc < bk || e < rc + iv || e > (bk + 1) * (rc) + ((rc - bk) * (rc - bk - 1)) / 2) return false;
	return true;
}

int memo[2][51][51][51];
int acc [2][51][51][51];
//int ways(int e, int rc, int bk, int iv) {
//	//printf("%d, %d, %d, %d\n", e, rc, bk, iv);
//	if(!valid(e, rc, bk, iv)) return 0;
//	int &r = memo[e][rc][bk][iv];
//	if(seen[e][rc][bk][iv] == tempo) return r;
//	seen[e][rc][bk][iv] = tempo;
//	if(e == 0) return !rc && !bk && !iv;
//	if(valid(e - 1, rc, bk, iv)) r = ways(e - 1, rc, bk, iv);
//	else r = ways(e - 1, rc - 1, bk, iv);
//	if(iv)
//		for(int i = bk - 1; i >= 0; i--)
//			r = mod(r + ways(e - 1, rc, i, iv - 1));
//	//printf("ways(%d, %d, %d, %d) = %d\n", e, rc, bk, iv, r);
//	return r;
//}

int main() {
	for_tests(tn, tt) {
		scanf("%d %d %d", &n, &m, &modn);
		for(int rc = 0; rc < n; rc++)
			for(int bk = 0; bk < n; bk++)
				for(int iv = 0; iv < n; iv++)
					memo[0][rc][bk][iv] = 0;
		memo[0][0][0][0] = 1;
		for(int e = 1; e <= m; e++) {
			int ei = (e & 1);
			for(int bk = 0; bk < n; bk++)
				for(int rc = bk; rc < n; rc++)
					for(int iv = 0; iv <= bk; iv++) {
						int &r = memo[ei][rc][bk][iv];
						r = 0;
						if(!valid(e, rc, bk, iv)) continue;
						if(valid(e - 1, rc, bk, iv)) r = memo[!ei][rc][bk][iv];
						else if(rc > 0) r = memo[!ei][rc - 1][bk][iv];
						if(iv && bk)
							r = mod(r + acc[!ei][rc][bk - 1][iv - 1]);
							//for(int i = bk - 1; i >= 0; i--)
							//	r = mod(r + memo[!ei][rc][i][iv - 1]);
						acc[ei][rc][bk][iv] = mod(r + (bk? acc[ei][rc][bk - 1][iv] : 0));
					}

			int ans = 0;
			for(int iv = 0; iv < n && iv <= e; iv++)
				for(int j = iv; j < n && j <= e - iv; j++)
					ans = mod(ans + memo[ei][min(n - 1, e - iv)][j][iv]);
			printf("%d ", ans);
		}
		putchar('\n');
	}
}
