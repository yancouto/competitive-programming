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
typedef pair<pii, int> piii;

const int N = 112345;
map<piii, set<piii>> adj3;
map<pii, set<pii>> adj2;
map<pii, int> seen2;
map<piii, int> seen3;

bool dfs3(piii u, piii p) {
	if(seen3[u] == 2) return false;
	//printf("at %d,%d,%d\n", u.fst.fst, u.fst.snd, u.snd);
	if(seen3[u] == 1) return true;
	seen3[u] = 1;
	for(piii v : adj3[u])
		if(p != v && dfs3(v, u))
			return true;
	seen3[u] = 2;
	//printf("done %d,%d,%d\n", u.fst.fst, u.fst.snd, u.snd);
	return false;
}

bool dfs2(pii u, pii p) {
	if(seen2[u] == 1) return true;
	if(seen2[u] == 2) return false;
	seen2[u] = 1;
	for(pii v : adj2[u])
		if(p != v && dfs2(v, u))
			return true;
	seen2[u] = 2;
	return false;
}

int main() {
	int i, k;
	scanf("%d", &k);
	piii a, b;
	for(i = 0; i < k; i++) {
		scanf("%d %d %d %d %d %d", &a.fst.fst, &a.fst.snd, &a.snd, &b.fst.fst, &b.fst.snd, &b.snd);
		if(a != b) adj3[a].insert(b);
		if(a != b) adj3[b].insert(a);
		if(a.fst != b.fst) adj2[a.fst].insert(b.fst);
		if(a.fst != b.fst) adj2[b.fst].insert(a.fst);
	}
	bool has = false;
	for(auto &e : adj3) {
		if(seen3[e.fst]) continue;
		if(dfs3(e.fst, piii(pii(-1, -1), -1))) { has = true; break; }
	}
	if(has) puts("True closed chains");
	else puts("No true closed chains");
	has = false;
	for(auto &e : adj2) {
		if(seen2[e.fst]) continue;
		if(dfs2(e.fst, pii(-1, -1))) { has = true; break; }
	}
	if(has) puts("Floor closed chains");
	else puts("No floor closed chains");
}
