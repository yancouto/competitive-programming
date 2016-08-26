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
const ll modn = 1000000;
inline ll mod(ll x) { return x % modn; }
#define srt first
#define rat second
const int N = 11234;

pii p[N];

int bit[N][2][52], b[N], mrk[N];
ll get(int i, int up, int k) {
	int sum = 0;
	for(i += 2; i; i -= (i & -i))
		sum += bit[i][up][k];
	return mod(sum);
}
ll get(int l, int r, int up, int k) {
	if(k < 0) return 0;
	return mod(get(r, up, k) - get(l - 1, up, k) + modn);
}
ll dp[N][3][53];
void add(int i, int up, int k, int x) {
	printf("adding %d to bit(%d, %d, %d)\n", x, i, up, k);
	for(i += 2; i < N; i += (i & -i))
		bit[i][up][k] = mod(bit[i][up][k] + x);
}

int main() {
	int i, n, K, k, up;
	for_tests(t, tt) {
		memset(bit, 0, sizeof bit);
		scanf("%d %d", &n, &K);
		for(i = 0; i < n; i++) {
			scanf("%d %d", &p[i].srt, &p[i].rat);
			b[i] = p[i].rat;
		}
		sort(b, b + n);
		int bn = unique(b, b + n) - b;
		sort(p, p + n);
		for(i = n - 1; i >= 0; i--) {
			p[i].rat = lower_bound(b, b + bn, p[i].rat) - b;
			printf("i[%d] rat %d\n", i, p[i].rat);
			for(k = 0; k <= K; k++)
				for(up = 0; up <= 2; up++) {
					ll &r = dp[i][k][up];
					r = (k == 0);
					r += get(p[i].rat + 1, n + 1, 1, k - (up == 0));
					r += get(0, p[i].rat - 1, 0, k - (up == 1));
					r = mod(r);
					printf("dp[i=%d][k=%d][up=%d] = %d\n", i, k, up, (int)r);
				}
			for(k = 0; k <= K; k++)
				for(up = 0; up <= 1; up++) {
					add(p[i].rat, k, up, -get(p[i].rat, p[i].rat, k, up));
					add(p[i].rat, k, up, dp[i][k][up]);
				}
		}
		memset(mrk, 0, sizeof mrk);
		ll tot = 0;
		for(i = 0; i < n; i++)
			if(!mrk[p[i].rat]) {
				tot += dp[i][K][2];
				mrk[p[i].rat] = 1;
			}
		printf("Case %d: %d\n", tt, (int) mod(tot));
	}
}
