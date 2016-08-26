#include <cstdio>
#include <cstring>
#include <algorithm>
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

int bad[27][27][27];
char s[23];
ull memo[22][27][27][2];
int seen[22][27][27][2], tempo;
ull solve(int i, int p2, int p1, bool pre) {
	if(!s[i]) return 1;
	ull &r = memo[i][p2][p1][pre];
	if(seen[i][p2][p1][pre] == tempo) return r;
	seen[i][p2][p1][pre] = tempo;
	r = 0;
	for(int d = 'a'; d <= 'z'; d++) {
		if(pre && d > s[i]) break;
		if(bad[d - 'a' + 1][0][0] || bad[p1][d - 'a' + 1][0] || bad[p2][p1][d - 'a' + 1]) continue;
		r += solve(i + 1, p1, d - 'a' + 1, pre && d == s[i]);
	}
	return r;
}

ll sz[22];
int main() {
	int n, m, i, j, p, x;
	for_tests(t, tt) {
		scanf("%d %d", &n, &m);
		memset(bad, 0, sizeof bad);
		for(i = 0; i < n; i++) {
			s[0] = s[1] = s[2] = 0;
			scanf("%s", s);
			bad[s[0] - 'a' + 1][max(0, s[1] - 'a' + 1)][max(0, s[2] - 'a' + 1)] = 1;
		}
		for(i = 1; i <= 20; i++) {
			s[i - 1] = 'z';
			s[i] = 0;
			tempo++;
			sz[i] = solve(0, 0, 0, true);
		}
		for(i = 0; i < m; i++) {
			if(scanf("%d", &x)) {
				int q;
				for(q = 0; x > sz[q]; q++)
					x -= sz[q];
				for(j = 0; j < q; j++)
					s[j] = 'z';
				s[q] = 0;
				tempo++;
				for(j = 0; j < q; j++) {
					int l;
					for(l = 'a'; l <= 'z'; l++) {
						int p1 = 0, p2 = 0;
						if(j > 0) p2 = s[j - 1] - 'a' + 1;
						if(j > 1) p1 = s[j - 2] - 'a' + 1;
						if(bad[l - 'a' + 1][0][0] || bad[p2][l - 'a' + 1][0] || bad[p1][p2][l - 'a' + 1]) continue;
						if(solve(j + 1, p2, l - 'a' + 1, false) >= x) break;
						else x -= solve(j + 1, p2, l - 'a' + 1, false);
					}
					s[j] = l;
				}
				puts(s);
			} else {
				scanf("%s", s);
				int k = strlen(s); ull v = 0;
				for(j = 0; j < k; j++)
					v += sz[j];
				tempo++;
				printf("%llu\n", solve(0, 0, 0, true) + v);
			}
		}
	}
}
