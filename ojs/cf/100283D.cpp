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
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }

int rs[1003], cs[1003], rn, cn;
int memo[1004][1004];
int& me(int i, int j) { return memo[i & 1][j]; }
int main() {
	freopen("rooks.in", "r", stdin);
	int i, k, n, m, r, c;
	for_tests(t, tt) {
		scanf("%*d %*d %d", &k);
		for(i = 0; i < k; i++) {
			scanf("%d %d", &r, &c);
			rs[i] = --r; cs[i] = --c;
		}
		sort(rs, rs + k); sort(cs, cs + k);
		rn = unique(rs, rs + k) - rs;
		cn = unique(cs, cs + k) - cs;
		n = max(rn, cn); m = min(rn, cn);
		printf("n: %d m: %d\n", n, m);
		for(int cover = 0; cover <= m; cover++)
			me(n, cover) = (cover == m);
		for(int i = n - 1; i >= 0; i--)
			for(int cover = 0; cover <= m; cover++) {
				int &r = me(i, cover);
				r = ll(cover) * me(i + 1, cover);
				if(cover < m) r += ll(m - cover) * me(i + 1, cover + 1);
				r = mod(r);
				printf("me(%d, %d) = %d\n", i, cover, r);
			}
		printf("Case %d: %d %d\n", tt, n, me(0, 0));
	}
}
