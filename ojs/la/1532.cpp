#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef unsigned long long ull;
typedef long long ll;
typedef long double ld;
typedef pair<int, ll> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
template<typename T> inline T abs(T t) { return t < 0? -t : t; }
const ull modn = 1000000007;
inline ull mod(ull x) { return x % modn; }
inline int num(char a, char b) { return ((a - 'a') * ('z' - 'a' + 1) + (b - 'a')); }
vector<pii> adj[26 * 26 + 10];
ll dist[26 * 26 + 10];

bool neg_cyc(ll t) {
	int k, i, j;
	memset(dist, 0, sizeof dist);
	for(k = 0; k < 26 * 26 + 1; k++) {
		bool any = false;
		for(i = 'a'; i <= 'z'; i++)
			for(j = 'a'; j <= 'z'; j++)
				for(pii p : adj[num(i, j)])
					if(dist[p.fst] > dist[num(i, j)] + -(p.snd - t))
						dist[p.fst] = dist[num(i, j)] + -(p.snd - t), any = true;
		if(!any) return false;
	}
	return true;
}

char str[2000];
int main() {
	int i, j, n;
	while(true) {
		scanf("%d", &n);
		if(!n) return 0;
		for(i = 'a'; i <= 'z'; i++)
			for(j = 'a'; j <= 'z'; j++)
				adj[num(i, j)].clear();
		for(i = 0; i < n; i++) {
			scanf("%s", str); int l = strlen(str);
			if(l == 1) continue;
			adj[num(str[0], str[1])].pb(pii(num(str[l - 2], str[l - 1]), 10000ll * l));
		}
		ll l = 0, r = 1002ll * 10000ll;
		while(l < r) {
			ll mid = (l + r) / 2;
			if(neg_cyc(mid)) l = mid + 1;
			else r  = mid;
		}
		if(!l) puts("No solution.");
		else printf("%.2f\n", l / 10000.);
	}
}
