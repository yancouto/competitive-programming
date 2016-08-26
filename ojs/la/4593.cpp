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
inline int count_1s(int x) { return __builtin_popcount(x); }
inline int count_1s(ull x) { return __builtin_popcountll(x); }
template<typename T> inline T abs(T t) { return t < 0? -t : t; }
const ull modn = 1000000007;
inline ull mod(ull x) { return x % modn; }
#ifndef ONLINE_JUDGE
#	define debug(args...) fprintf(stderr, "%3d| ", __LINE__); fprintf(stderr, args); fprintf(stderr, "\n");
#else
#	define debug(args...)
#endif

ull gcd(ull a, ull b) {
	if(a < b) gcd(b, a);
	if(b == 0) return a;
	return gcd(b, a % b);
}

int pos[100009];
ull mdc[100009];
int main() {
	ull x; int i, j, k, n;
	int pi;
	for_tests(t, tt) {
		pi = 0;
		scanf("%d", &n);
		scanf("%llu", &x);
		pos[pi] = 0;
		mdc[pi++] = x;
		ull mx = x;
		for(i = 1; i < n; i++) {
			scanf("%llu", &x);
			for(j = 0; j < pi; j++)
				mdc[j] = gcd(mdc[j], x);
			k = 0;
			for(j = 0; j < pi; j++){ 
				mdc[k] = mdc[j];
				pos[k] = pos[j];
				if(k == 0 || mdc[k] != mdc[k - 1]) {
					if(mdc[k] * ull(i - pos[k] + 1) > mx)
						mx = mdc[k] * ull(i - pos[k] + 1);
					k++;
				}
			}
			pi = k;
			if(x != mdc[pi - 1]) {
				pos[pi] = i;
				mdc[pi++] = x;
				if(x > mx) mx = x;
			}
		}
		printf("%llu\n", mx);
	}
	return 0;
}