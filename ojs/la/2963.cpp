#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef unsigned long long ull;
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
template<typename T> inline T abs(T t) { return t < 0? -t : t; }
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }
int x, y;
vector<pii> adj[1509];
vector<int> path, p2;
bool got[1509]; int loc[1509];
bool go(int u, int p, int color, bool has_key) {
	if(!has_key && loc[color] == u) p = -1, has_key = true;
	for(pii e : adj[u]) {
		if(e.fst == p) continue;
		if(has_key && e.snd == color) {
			got[color] = true;
			p2.pb(e.fst);
			p2.pb(u);
			x = e.fst;
			return true;
		}
		if(e.snd != -1 && !got[e.snd]) continue;
		if(go(e.fst, u, color, has_key)) {
			p2.pb(u);
			return true;
		}
	}
	return false;
}
int seekey[1509], seedoor[1509], t, has[1509];
void see(int u, int p) {
	if(has[u] != -1) seekey[has[u]] = t;
	for(pii e : adj[u]) {
		if(e.fst == p) continue;
		if(e.snd != -1) seedoor[e.snd] = t;
		if(e.snd != -1 && !got[e.snd]) continue;
		see(e.fst, u);
	}
}

bool dfs(int u, int p) {
	if(u == y) { p2.pb(u); return true; }
	for(pii e : adj[u]) {
		if(e.fst == p) continue;
		if(e.snd != -1 && !got[e.snd]) continue;
		if(dfs(e.fst, u)) { p2.pb(u); return true; }
	}
	return false;
}

int main() {
	int v, c, i, a, b, l;
	while(scanf("%d %d %d %d", &v, &c, &x, &y) != EOF && v) {
		path.clear();
		path.pb(x);
		for(i = 0; i < v; i++)
			adj[i].clear(), has[i] = -1;
		for(i = 0; i < c; i++) {
			scanf("%d", &loc[i]), got[i] = false;
			has[loc[i]] = i;
		}
		for(i = 0; i < v - 1; i++) {
			scanf("%d %d %d", &a, &b, &l);
			adj[a].pb(pii(b, l));
			adj[b].pb(pii(a, l));
		}
		while(true) {
			t++;
			see(x, -1);
			bool d = false;
			for(i = 0; i < c; i++) {
				if(got[i] || seekey[i] != t || seedoor[i] != t) continue;
				d = true;
				go(x, -1, i, false);
				reverse(p2.begin(), p2.end());
				path.insert(path.end(), p2.begin(), p2.end());
				p2.clear();
			}
			if(!d) break;
		}
		if(dfs(x, -1)) {
			reverse(p2.begin(), p2.end());
			path.insert(path.end(), p2.begin(), p2.end());
			p2.clear();
			int j = 1;
			for(i = 1; i < path.size(); i++)
				if(path[i] != path[i - 1])
					path[j++] = path[i];
			path.resize(j);
			printf("%d:", path.size() - 1);
			for(int k : path)
				printf(" %d", k);
			putchar('\n');
		} else puts("Impossible");
	}
}
