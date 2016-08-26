// TLE
#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef unsigned long long ull;
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
template<typename T> inline T abs(T t) { return t < 0? -t : t; }
const ll modn = 1000000009;
inline ll mod(ll x) { return x % modn; }

ll memo[302][302][2][2];

inline ll& solve2(int n, int k, bool fst, bool fake) { return memo[n][k][fst][fake]; }
//inline ll solve(int n, int k, bool fst, bool fake) {
//	ll &r = memo[301-n][k][fst][fake];
//	if(n < 3) return r = (k == 0);
//	if(n == 3) return r = ((fake? (k == 0) : (k == 1)));
//	if(fst) r = solve2(n, k, false, fake);
//	else r = solve2(n - 1, k, false, true);
//	int i, j;
//	if(fst)
//		for(i = 2; i < n - 1; i++) {
//			for(j = 0; j <= k; j++)
//				r = mod(r + solve2(i + 1, j, false, false) * solve2(n - i + 1, k - j, true, fake));
//		}
//	else
//		for(i = 3; i < n; i++) {
//			for(j = 0; j <= k; j++)
//				r = mod(r + solve2(i, j, false, false) * solve2(n + 2 - i, k - j, false, fake));
//		}
//	return r;
//}

int main() {
	int N, K;
	scanf("%d %d", &N, &K);
	int n, k, fst, fake, i, j;
	for(n = 0; n < 3; n++)
		for(k = 0; k <= K; k++)
			for(fake = 0; fake <= 1; fake++)
				for(fst = 0; fst <= 1; fst++)
					solve2(n, k, fst, fake) = (k == 0);
	for(k = 0; k <= K; k++)
		for(fake = 0; fake <= 1; fake++)
			for(fst = 0; fst <= 1; fst++)
				solve2(3, k, fst, fake) = ((fake? (k == 0) : (k == 1)));
	for(n = 4; n <= N; n++) {
		for(k = 0; k <= K; k++)
			for(fake = 0; fake <= 1; fake++) {
				ll &r = solve2(n, k, false, fake);
				r = solve2(n - 1, k, false, true);
				for(i = 3; i < n; i++)
					for(j = 0; j <= k; j++)
						r = mod(r + solve2(i, j, false, false) * solve2(n + 2 - i, k - j, false, fake));
			}
		for(k = 0; k <= K; k++)
			for(fake = 0; fake <= 0; fake++) {
				ll &r = solve2(n, k, true, fake);
				r = solve2(n, k, false, fake);
				for(i = 2; i < n - 1; i++)
					for(j = 0; j <= k; j++)
						r = mod(r + solve2(i + 1, j, false, false) * solve2(n - i + 1, k - j, true, fake));
			}
	}
	printf("%d\n", (int) solve2(N, K, true, false));
}
