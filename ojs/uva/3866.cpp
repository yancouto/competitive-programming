#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef unsigned long long ull;
typedef long long ll;
typedef long double ld;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
inline int count_1s(int x) { return __builtin_popcount(x); }
inline int count_1s(ull x) { return __builtin_popcountll(x); }
template<typename T> inline T abs(T t) { return t < 0? -t : t; }
const ull modn = 1000000;
inline ull mod(ull x) { return x % modn; }
#ifndef ONLINE_JUDGE
#	define debug(args...) fprintf(stderr, "%3d| ", __LINE__); fprintf(stderr, args); fprintf(stderr, "\n");
#else
#	define debug(args...)
#endif
int n;
int p[1009][2];

ull dist(int i, int j) {
	return ull(p[i][0] - p[j][0]) * ull(p[i][0] - p[j][0]) + ull(p[i][1] - p[j][1]) * ull(p[i][1] - p[j][1]);
}
ull ds[1000009];
int main() {
	int i, j;
	for_tests(t, tt) {
		scanf("%d", &n);
		for(i = 0; i < n; i++)
			scanf("%d %d", &p[i][0], &p[i][1]);
		int dn = 0;
		for(i = 0; i < n; i++)
			for(j = i + 1; j < n; j++)
				ds[dn++] = dist(i, j);
		sort(ds, ds + dn);
		printf("Case %d: %d\n", tt, int((unique(ds, ds + dn) - ds) + 1));
	}
	return 0;
}
