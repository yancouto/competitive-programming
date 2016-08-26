#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef unsigned long long ull;
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }
#ifdef ONLINE_JUDGE
#	define LLD "%I64d"
#	define debug(args...) {}
#else
#	define LLD "%lld"
#	define debug(args...) fprintf(stderr, args)
#endif

int val[312][312];
vector<pii> v[312*312];

int main() {
	int i, j, n, m, p, x;
	scanf("%d %d %d", &n, &m, &p);
	for(i = 0; i < n; i++)
		for(j = 0; j < m; j++) {
			scanf("%d", &x);
			v[x].pb(pii(i, j));
		}
	map<int, pii> mp[4];
	for(i = p; i >= 1; i--) {
		if(i < p) {
			for(pii e : v[i]) {
				val[e.fst][e.snd] = INT_MAX;
				for(j = 0; j < 4; j++) {
					auto it = mp[j].lower_bound(-((j & 1) * 2 - 1) * e.fst - ((j & 2) - 1) * e.snd);
					if(it == mp[j].end()) continue;
					val[e.fst][e.snd] = min(val[e.fst][e.snd], abs(e.fst - it->snd.fst) + abs(e.snd - it->snd.snd) + val[it->snd.fst][it->snd.snd]);
				}
				debug("val[%d][%d] = %d\n", e.fst, e.snd, val[e.fst][e.snd]);
			}
		}
		for(j = 0; j < 4; j++) {
			mp[j].clear();
			for(pii e : v[i])
				mp[j][((j & 1) * 2 - 1) * e.fst + ((j & 2) - 1) * e.snd + val[e.fst][e.snd]] = e;
		}
	}
	int b = INT_MAX;
	for(pii e : v[1])
		b = min(b, val[e.fst][e.snd] + e.fst + e.snd);
	printf("%d\n", b);
}
