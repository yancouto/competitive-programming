#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define fst first
#define snd second
typedef pair<int, int> pii;

vector<pii> adj[100];
int t[100], r[100];
int d[110];

bool ok(int X) {
	int i, k;
	for(int i = 0; i <= 24; i++) adj[i].clear();
	adj[0].pb(pii(24, X));
	adj[24].pb(pii(0, -X));
	for(int i = 0; i < 24; i++) {
		adj[i].pb(pii(i + 1, t[i + 1]));
		if(i + 8 <= 24) {
			adj[i + 8].pb(pii(i, -r[i + 8]));
		} else {
			int j = ((i - 1 + 8) % 24) + 1;
			adj[j].pb(pii(i, X - r[j]));
		}
	}
	for(i = 0; i <= 24; i++) d[i] = 0;
	for(k = 0; k <= 24; k++)
		for(i = 0; i <= 24; i++)
			for(pii p : adj[i])
				d[p.fst] = min(d[p.fst], d[i] + p.snd);
	for(i = 0; i <= 24; i++)
		for(pii p : adj[i])
			if(d[i] + p.snd < d[p.fst])
				return false;
	return true;
}

int main() {
	int i, tt, n, x;
	scanf("%d", &tt);
	while(tt--) {
		for(i = 1; i <= 24; i++) scanf("%d", &r[i]), t[i] = 0;
		scanf("%d", &n);
		for(i = 0; i < n; i++) { scanf("%d", &x); t[x + 1]++; }
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
