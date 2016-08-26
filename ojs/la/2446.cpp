#include <bits/stdc++.h>
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
#ifndef ONLINE_JUDGE
#	define debug(args...) {fprintf(stderr, "%3d| ", __LINE__); fprintf(stderr, args); fprintf(stderr, "\n");}
#else
#	define debug(args...) {}
#endif
const ull modn = 1000000007;
inline ull mod(ull x) { return x % modn; }
int n;
int a[9][2];
int perm[9];

bool poss(int k) {
	int i;
	for(i = 0; i < n; i++)
		perm[i] = i;
	do {
		int s = -1;
		for(i = 0; i < n; i++) {
			//printf("%d ok\n", s);
			//printf("(%d, %d)\n", a[perm[i]][0], a[perm[i]][1]);
			if(s > a[perm[i]][1]) break;
			s = max(s, a[perm[i]][0]) + k;
			//printf("new %d\n", s);
		}
		//puts("xablau");
		if(i == n) return true;
	} while(next_permutation(perm, perm + n));
	return false;
}

int main() {
	int i, j, t = 0;
	while(true) {
		scanf("%d", &n);
		if(!n) return 0;
		for(i = 0; i < n; i++) {
			scanf("%d %d", &a[i][0], &a[i][1]);
			a[i][0] *= 60000;
			a[i][1] *= 60000;
		}
		int l = 0, r = 1443*63*1000;
		while(l < r) {
			int m = (l + r + 1) / 2;
			if(poss(m)) l = m;
			else r = m - 1;
		}
		printf("Case %d: %d:%02d\n", ++t, l / 60000, ((l/1000) % 60) + ((l % 1000) >= 500));
	}
}
