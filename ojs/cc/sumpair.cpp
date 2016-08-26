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
int n, d, a[100009];

int main() {
	int i, j;
	for_tests(t, tt) {
		scanf("%d %d", &n, &d);
		for(i = 0; i < n; i++)
			scanf("%d", &a[i]);
		ull tot = 0;
		sort(a, a  + n);
		for(i = n - 1; i > 0; ) {
			if(a[i] - a[i - 1] < d) {
				tot += a[i] + a[i - 1];
				i -= 2;
			} else i--;
		}
		printf("%llu\n", tot);
	}
	return 0;
}
