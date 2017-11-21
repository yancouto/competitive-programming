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

set<int> seen2;
deque<int> tmp;
map<int, int> co, cp;
set<int> seen;
map<int, vector<pii>> adj;
int is_bip[N];
int bad; ll badval;
bool any;

bool bip(int cn, int h, int u, int p, ll acc, int c) {
	if(seen.count(u)) {
		if(co[u] == c) return true;
		is_bip[cn] = false;
		if(any) return false;
		tmp.pb(u);
		any = true;
		while(tmp.front() != u)
			tmp.pop_front();
		//for(int x : tmp) printf("%d ", x); putchar('\n');
		ll tot = 0;
		for(int i = 0; i < int(tmp.size()) - 1; i++)
			for(pii e : adj[tmp[i]])
				if(e.fst == tmp[i + 1]) {
					tot += (i & 1)? -e.snd : e.snd;
					break;
				}
		bad = u;
		assert(!(tot % 2));
		badval = tot / 2;
		return false;
	}
	seen.insert(u);
	cp[u] = cn;
	tmp.pb(u);
	co[u] = c;
	for(pii e : adj[u])
		bip(cn, h + 1, e.fst, u, acc + e.snd * c, -c);
	if(!any) tmp.pop_back();
}

map<int, ll> val;
void go(int u, ll v) {
	seen2.insert(u);
	val[u] = v;
	for(pii e : adj[u])
		if(!seen2.count(e.fst))
			go(e.fst, e.snd - v);
}

int main() {
	int i, m, q, a, b, w;
	while(scanf("%d %d", &m, &q) != EOF && (m || q)) {
		co.clear(); cp.clear(); adj.clear(); seen.clear(); seen2.clear(); val.clear();
		vector<int> vs;
		for(i = 0; i < m; i++) {
			scanf("%d %d %d", &a, &b, &w);
			if(a == b) w *= 2;
			adj[a].pb(pii(b, w));
			adj[b].pb(pii(a, w));
			vs.pb(a); vs.pb(b);
		}
		sort(vs.begin(), vs.end());
		vs.erase(unique(vs.begin(), vs.end()), vs.end());
		int cn = 0;
		for(int u : vs)
			if(!seen.count(u)) {
				is_bip[cn] = true;
				any = false;
				tmp.clear();
				bip(cn, 0, u, u, 0, 1);
				if(is_bip[cn]) bad = u, badval = 0;
				go(bad, badval);
				cn++;
			}
		while(q--) {
			scanf("%d %d", &a, &b);
			if(!co.count(a) || !co.count(b)) { puts("*"); continue; }
			if(cp[a] != cp[b]) { puts("*"); continue; }
			if(is_bip[cp[a]] && co[a] == co[b]) { puts("*"); continue; }
			printf("%lld\n", a == b? val[a] : val[a] + val[b]);
		}
		puts("-");
	}
}
