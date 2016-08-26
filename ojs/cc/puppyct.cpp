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
const ull modn = 1000000007;
inline ull mod(ull x) { return x % modn; }
const int MAX = 2000009;
int b[4][MAX];
int get(int i, int f) {
	int sum = 0; f += 2;
	while(f) {
		sum += b[i][f];
		f -= (f & -f);
	}
	return sum;
}
inline int get(int i, int f, int t) {
	return get(i, t) - get(i, f - 1);
}
int add1(int i, int f) {
	f += 2;
	while(f < MAX) {
		b[i][f]++;
		f += (f & -f);
	}
}
int d1[MAX], d2[MAX];

int main() {
	int n, k, i, k1, k2, x, y, sz1, sz2;
	for_tests(t, tt) {
		memset(b, 0, sizeof b);
		memset(d1, 0, sizeof d1);
		memset(d2, 0, sizeof d2);
		ull tot = 0;
		scanf("%d %d", &n, &k);
		for(i = 0; i < k; i++) {
			scanf("%d %d", &x, &y);
			k1 = x + y;
			k2 = x - y;
			sz1 = (n - abs(n + 1 - k1));
			sz2 = (n - abs(k2));
			//printf("%llu before\n", tot);
			if(!d1[k1]) {
				d1[k1] = 1;
				//printf("1size %d\n", sz1);
				tot += sz1;
				int conf = get(sz2 & 1, n - sz1, n + sz1);
				//printf("conf %d\n", conf);
				tot -= conf;
				add1(2 + (sz1 & 1), k1);
			}
			if(!d2[n + k2]) {
				d2[n + k2] = 1;
				//printf("2size %d\n", sz2);
				tot += sz2;
				int conf = get(2 + (sz1 & 1), (n + 1) - sz2, (n + 1) + sz2);
				//printf("conf %d\n", conf);
				tot -= conf;
				add1(sz2 & 1, n + k2);
			}
			//printf("%llu after\n", tot);
		}
		printf("%llu\n", ull(n) * n - tot);
	}
	return 0;
}
