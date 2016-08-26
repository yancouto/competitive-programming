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
const int MAX = 300009;
int n;
ull xo[MAX];
ull num[MAX];
char str[MAX];
inline int val(char c) {
	if(c >= 'a' && c <= 'z') return c - 'a';
	else return c - 'A' + ('z' - 'a' + 1);
}

int main() {
	int i, j;
	while(scanf("%d %s", &n, str) != EOF) {
		for(i = 1; i <= n; i++) {
			xo[i] = xo[i - 1] ^ (1ull << val(str[i - 1]));
		}
		sort(xo + 1, xo + n + 1);
		j = 0;
		for(i = 0; i <= n; i++) {
			xo[j] = xo[i];
			if(j == 0 || xo[j] != xo[j - 1])
				num[j++] = 1;
			else num[j - 1]++;
		}
		n = j;
		ull tot = 0;
		for(j = 0; j < n; j++) {
			for(i = 0; i < 52; i++) {
				ull x = 1ull << i;
				ull *l = lower_bound(xo, xo + n, x ^ xo[j]);
				if(l != xo + n && *l == (x ^ xo[j]))
					tot += num[l - xo] * num[j];
			}
			tot += (num[j] *(num[j] - 1));
		}
		tot /= 2;
		printf("%llu\n", tot);
	}
	return 0;
}