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


struct ed { int u, v, w; };
const int N = 1123;

int R[N], ct[N], d[N];

bool ok(int x) {
	int i;
	vector<ed> es;
	for(i = 1; i <= 24; i++)
		es.pb(ed{i, 0, 0});
	for(i = 8; i <= 24; i++)
		es.pb(ed{i, i - 8, -R[i]});
	for(i = 1; i < 8; i++)
		es.pb(ed{i, i - 8 + 24, -R[i] + x});
	for(i = 1; i <= 24; i++)
		es.pb(ed{i - 1, i, ct[i]});
	es.pb(ed{0, 24, x});
	es.pb(ed{24, 0, -x});
	for(i = 0; i <= 24; i++) d[i] = 0;
	for(i = 0; i <= 24; i++)
		for(ed e : es)
			d[e.v] = min(d[e.v], d[e.u] + e.w);
	for(ed e : es)
		if(d[e.v] > d[e.u] + e.w)
			return false;
	return true;
}

int main() {
	int i, n, x;
	for_tests(tn, tt) {
		for(i = 1; i <= 24; i++) scanf("%d", &R[i]), ct[i] = 0;
		scanf("%d", &n);
		for(i = 0; i < n; i++) {
			scanf("%d", &x);
			ct[x+1]++;
		}
		if(!ok(n)) { puts("No Solution"); continue; }
		int l = 0, r = n;
		while(l < r) {
			int m = (l + r) / 2;
			if(ok(m)) r = m;
			else l = m + 1;
		}
		printf("%d\n", l);
	}
}
