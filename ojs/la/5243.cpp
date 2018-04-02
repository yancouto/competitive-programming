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

int se[2][N];

vector<int> cyc;
int tt;
vector<int> adj[N];

bool try_(int u, int p, int t) {
	if(u == t && p == 0) return true;
	se[p][u] = tt;
	cyc.pb(u);
	for(int v : adj[u])
		if(se[!p][v] != tt)
			if(try_(v, !p, t))
				return true;
	cyc.pop_back();
	return false;
}

int st[N], sn;
int d[N], tempo, low[N], seen[N], cn, co[N];


bool go(int u) {
	seen[u] = tt;
	st[sn++] = u;
	low[u] = d[u] = tempo++;
	for(int v : adj[u])
		if(seen[v] == tt)
			low[u] = min(low[u], d[v]);
		else {
			if(go(v)) return true;
			low[u] = min(low[u], low[v]);
		}
	if(low[u] == d[u]) {
		int a; cn++;
		//printf("cmp %d\n", cn);
		do {
			a = st[--sn];
			//printf(">%d\n", a);
			co[a] = cn;
			d[a] = INT_MAX;
		} while(a != u);
		for(int v : adj[u])
			if(co[v] == co[u]) {
				cyc.pb(u);
				if(try_(v, 0, u)) return true;
				cyc.clear();
				break;
			}
	}
	return false;
}

int mrk[N], lst[N];

void clean_cyc() {
	vector<int> nc;
	for(int i = 0; i < int(cyc.size()); i++) {
		nc.pb(cyc[i]);
		if(mrk[cyc[i]] == tt) {
			if((i - lst[cyc[i]]) % 2) {
				vector<int> nnc;
				for(nc.pop_back(); nc.back() != cyc[i]; nc.pop_back())
					nnc.pb(nc.back());
				nnc.pb(cyc[i]);
				reverse(nnc.begin(), nnc.end());
				nc = nnc;
				break;
			} else {
				for(nc.pop_back(); nc.back() != cyc[i]; nc.pop_back())
					mrk[nc.back()] = 0;
			}
		} else mrk[cyc[i]] = tt, lst[cyc[i]] = i;
	}
	cyc = nc;
}

int main() {
	int i, n, m, a, b;
	for_tests(tn, ttt) {
		::tt++;
		scanf("%d %d", &n, &m);
		for(i = 0; i < m; i++) {
			scanf("%d %d", &a, &b); a--; b--;
			adj[a].pb(b);
		}
		cyc.clear();
		for(i = 0; i < n; i++)
			if(seen[i] != tt)
				if(go(i))
					break;
		if(!cyc.empty()) {
			clean_cyc();
			printf("1\n%d\n", int(cyc.size()));
			for(int x : cyc)
				printf("%d\n", x + 1);
		} else puts("-1");

		for(i = 0; i < n; i++) adj[i].clear();
	}

}
