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
#	define debug(args...) fprintf(stderr, "%3d| ", __LINE__); fprintf(stderr, args); fprintf(stderr, "\n");
#else
#	define debug(args...)
#endif
const ull modn = 1000000007;
inline ull mod(ull x) { return x % modn; }
int m, x, y;
int h[103];

int main() {
	int i, j;
	for_tests(t, tt) {
		scanf("%d %d %d", &m, &x, &y);
		memset(h, 0, sizeof h);
		x *= y;
		for(i = 0; i < m; i++) {
			scanf("%d", &y);
			for(j = y - x; j <= y + x; j++)
				if(j > 0 && j <= 100)
					h[j] = 1;
		}
		int empty = 0;
		for(i = 1; i <= 100; i++)
			empty += !h[i];
		printf("%d\n", empty);
	}
	return 0;
}
