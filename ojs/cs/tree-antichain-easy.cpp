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

const int N = 112345;
int mh;
vector<int> bh[N], adj[N];

void go(int u, int p, int h) {
	mh = max(mh, h);
	bh[h].pb(u);
	for(int v : adj[u])
		if(v != p)
			go(v, u, h + 1);
}

vector<int> p;
set<pii> es;

void add(int h) {
	vector<int> tmp;
	while(!bh[h].empty() && !p.empty() && es.count(pii(p.back(), bh[h].back()))) {
		tmp.pb(bh[h].back());
		bh[h].pop_back();
	}
	assert(!bh[h].empty());
	p.pb(bh[h].back()); bh[h].pop_back();
	for(int x : bh[h]) p.pb(x);
	for(int x : tmp) p.pb(x);
}

int main() {
	int i, n, a, b;
	for_tests(tn, tt) {
		scanf("%d", &n);
		for(i = 0; i < n; i++) adj[i].clear(), bh[i].clear();
		es.clear();
		for(i = 0; i < n - 1; i++) {
			scanf("%d %d", &a, &b); a--; b--;
			adj[a].pb(b); adj[b].pb(a);
			es.insert(pii(a, b));
			es.insert(pii(b, a));
		}
		for(i = 0; i < n; i++)
			if(adj[i].size() == n - 1)
				break;
		if(i < n) { puts("-1"); continue; }
		mh = 0;
		go(0, -1, 0);
		p.clear();
		if(mh == 2) {
			add(0); add(2); add(1);
		} else if(mh & 1) {
			for(i = 0; i < (mh + 1) / 2; i++)
				add(2 * i + 1);
			for(i = 0; i < (mh + 1) / 2; i++)
				add(2 * i);
		} else {
			for(i = 0; i <= mh; i++)
				add((2 * i) % (mh + 1));
		}
		for(int x : p) printf("%d ", x + 1);
		putchar('\n');
	}
}
