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
#ifndef ONLINE_JUDGE
#	define debug(args...) fprintf(stderr, "%3d| ", __LINE__); fprintf(stderr, args); fprintf(stderr, "\n");
#else
#	define debug(args...)
#endif
const ull modn = 1000000007;
inline ull mod(ull x) { return x % modn; }
int n;
char s1[1003], s2[1003];
int memo[1003][1003], tempo;

inline bool eq(char a, char b) { return abs(a - b) <= 1; }


int main() {
	int i, j, k;
	for_tests(t, tt) {
		scanf("%d %s %s", &n, s1, s2);
		tempo++;
		int mx = 0;
		for(i = 0; i < n; i++) {
			for(j = 0; j < n; j++) {
				if(memo[i][j] == tempo) continue;
				for(k = 0; i + k < n && j + k < n && eq(s1[i+k], s2[j+k]); k++) {
					mx = max(mx, k + 1);
					memo[i+k][j+k] = tempo;
				}
			}
		}
		if(mx >= (n + 1) / 2) puts("POSITIVE");
		else puts("NEGATIVE");
	}
	return 0;
}
