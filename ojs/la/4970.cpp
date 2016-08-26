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
const ull modn = 1000000007;
inline ull mod(ull x) { return x % modn; }

vector<ll> v[1 << 14][14];
int n; ll L, d[14][14];
void process(int bm) {
	int p[14], pn = 0, i;
	for(i = 0; i < n; i++)
		if(bm & (1 << i))
			p[pn++] = i;
	do {
		ll tot = 0;
		for(i = 0; i < pn - 1; i++)
			tot += d[p[i]][p[i+1]];
		v[bm][p[pn - 1]].pb(tot);
	} while(next_permutation(p + 1, p + pn));
}
bool ok;
void process2(int bm) {
	int p[14], pn = 0, i;
	for(i = 1; i < n; i++)
		if(bm & (1 << i))
			p[pn++] = i;
	p[pn++] = 0;
	do {
		ll tot = 0;
		for(i = 0; i < pn - 1; i++) {
			tot += d[p[i]][p[i + 1]];
		}
		vector<ll> &vv = v[(((1 << n) - 1) ^ bm) | 1 | (1 << p[0])][p[0]];
		if(binary_search(vv.begin(), vv.end(), L - tot)) {
			ok = true;
			return;
		}
	} while(next_permutation(p, p + pn - 1));
}


int main() {
	int i, j;
	while(scanf("%d %lld", &n, &L) != EOF) {
		for(i = 0; i < n; i++)
			for(j = 0; j < n; j++)
				scanf("%lld", &d[i][j]);
		for(i = 0; i < (1 << n); i++)
			for(j = 0; j < n; j++)
				v[i][j].clear();
		if(n == 2) {
			if(d[0][1] + d[1][0] == L) puts("possible");
			else puts("impossible");
			continue;
		}
		for(i = 1; i < (1 << n); i += 2)
			if(__builtin_popcount(i) == ((n + 1) / 2) + 1)
				process(i);
		for(i = 0; i < (1 << n); i++)
			for(j = 0; j < n; j++)
				sort(v[i][j].begin(), v[i][j].end());
		ok = false;
		for(i = 1; !ok && i < (1 << n); i += 2)
			if(__builtin_popcount(i) == (n / 2) + 1)
				process2(i);
		if(ok) puts("possible");
		else puts("impossible");
	}
	return 0;
}
