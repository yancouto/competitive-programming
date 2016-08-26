#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef unsigned long long ull;
typedef long long ll;
typedef double ld;
typedef pair<int, int> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
template<typename T> inline T abs(T t) { return t < 0? -t : t; }
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }
int b, s[1002], per[1002]; ld p[1002], f[102];
ld memo[2][1025][102];
ld& m(int i, int bm, int left) { return memo[i&1][bm][left]; }
int main() {
	int i, t, j, ss; ld pp;
	f[0] = 1;
	while(scanf("%d %d %lf", &b, &t, &f[1]) != EOF) {
		for(i = 2; i <= t; i++)
			f[i] = f[i - 1] * f[1];
		for(i = 0; i < b; i++) {
			scanf("%lf %d", &pp, &ss);
			for(j = 0; j < t; j++) {
				p[i * t + j] = pp * f[j];
				s[i * t + j] = ss;
				per[i * t + j] = i * t + j;
			}
		}
		sort(per, per + b * t, [](int i, int j) { return p[i] * s[i] > p[j] * s[j]; });
		memset(memo, 0, sizeof memo);
		for(i = b*t - 1; i >= 0; i--)
			for(int bm = 0; bm < (1 << b); bm++)
				for(int left = 1; left <= t; left++) {
					m(i, bm, left) = m(i + 1, bm, left);
					int j = per[i];
					if(bm & (1 << (j / t))) continue;
					ld sol = p[j] * (s[j] + m(i + 1, bm | (1 << (j / t)), left - 1)) + (1. - p[j]) * m(i + 1, bm, left - 1);
					m(i, bm, left) = max(m(i, bm, left), sol);
				}

		printf("%.12lf\n", m(0, 0, t));
	}
}
