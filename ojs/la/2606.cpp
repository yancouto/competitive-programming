// WAAA??
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
const int MAX = 1009;
int h[MAX], p[MAX];
bool cmp(int i, int j) { return h[i] < h[j]; }
vector<pii> adj[MAX];
ll s[MAX]; int n;

bool pos(ll x) {
	int i, j;
	for(i = 0; i < n; i++) s[i] = 0;
	int a = p[0], b = p[n-1];
	if(a < b) swap(a, b);
	adj[a].pb(pii(b, -x));
	for(j = 0; j < n; j++)
		for(i = 0; i < n; i++)
			for(int k = 0; k < adj[i].size(); k++) {
				pii p = adj[i][k];
				if(s[p.fst] > s[i] + p.snd)
					s[p.fst] = s[i] + p.snd;
			}
	for(i = 0; i < n; i++)
		for(int k = 0; k < adj[i].size(); k++) {
			pii p = adj[i][k];
			if(s[p.fst] > s[i] + p.snd) {
				adj[a].pop_back();
				return false;
			}
		}
	adj[a].pop_back();
	return true;
}

int main() {
	int i, j, d;
	while(true) {
		scanf("%d %d", &n, &d);
		if(!n) return 0;
		for(i = 0; i < n; i++) {
			scanf("%d", &h[i]);
			adj[i].clear();
			if(i > 0) adj[i].pb(pii(i-1, -1));
			p[i] = i;
		}
		sort(p, p + n, cmp);
		for(i = 0; i < n - 1; i++) {
			int a = p[i], b = p[i+1];
			if(a > b) swap(a, b);
			adj[a].pb(pii(b, d));
		}
		ll l = abs(p[0] - p[n-1]), r = 1900000000ll;
		if(!pos(l)) { puts("-1"); continue; }
		while(l < r) {
			int m = (l + r + 1) / 2;
			if(pos(m)) l = m;
			else r = m - 1;
		}
		printf("%lld\n", l);
	}
}
