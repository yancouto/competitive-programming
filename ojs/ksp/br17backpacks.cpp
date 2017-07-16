#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }

int w[112], c[112];

pii ans[1 << 24];
int p[1 << 24], pn;
vector<int> ss[30];

int main() {
	int v, b, i, j;
	scanf("%d %d", &v, &b);
	for(i = 0; i < v; i++) scanf("%d", &w[i]);
	for(i = 0; i < b; i++) scanf("%d", &c[i]);
	sort(c, c + b, greater<int>());
	for(i = 0; i < (1 << v); i++)
		ss[__builtin_popcount(i)].pb(i);
	for(i = 0; i <= 25; i++)
		for(int j : ss[i])
			p[pn++] = j;
	ans[0] = pii(0, 0);
	for(int _i = 1; _i < (1 << v); _i++) {
		i = p[_i];
		ans[i] = pii(b, INT_MAX);
		int cp = i;
		while(cp) {
			j = __builtin_ctz(cp);
			pii x = ans[i ^ (1 << j)];
			if(x.snd + w[j] > c[x.fst]) x.fst++, x.snd = 0;
			if(x.fst < b && x.snd + w[j] <= c[x.fst])
				ans[i] = min(ans[i], pii(x.fst, x.snd + w[j]));
			cp ^= (1 << j);
		}
		if(ans[i].fst == b) { puts("NIE"); return 0; }
	}
	printf("%d\n", ans[(1 << v) - 1].fst +1);
}
