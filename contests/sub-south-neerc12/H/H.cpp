#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> pii;
#define pb push_back
#define fst first
#define snd second

const int N = 112345;
int keep[N];
vector<int> adj[N];
int n, m;
int c[N], id[N];

bool bip(int u, int C) {
	if(keep[u]) return true;
	if(c[u] != -1 && c[u] != C) return false;
	if(c[u] != -1) return true;
	c[u] = C;
	for(int v : adj[u])
		if(!bip(v, 3 - C))
			return false;
	return true;
}

vector<int> cs[2];

void end() {
	memset(c, -1, sizeof c);
	for(int i = 1; i <= n; i++) if(!keep[i] && c[i] == -1) bip(i, 1);
	for(int i = 1; i <= n; i++)
		if(!keep[i])
			cs[c[i] - 1].pb(i);
	for(int c = 0; c < 2; c++) {
		sort(cs[c].begin(), cs[c].end());
		printf("%d", int(cs[c].size()));
		for(int x : cs[c]) printf(" %d", x);
		putchar('\n');
	}
	exit(0);
}

pii go(int i, int j) {
	if(adj[j].size() == 4) return pii(0, j);
	for(int x : adj[j])
		if(x != i) {
			pii e = go(j, x);
			e.fst++;
			return e;
		}
}

deque<int> all;
void GO(int o, int i, int j) {
	if(j == o) return;
	//printf("all.pb(%d)\n", j);
	all.pb(j);
	for(int x : adj[j])
		if(i != go(j, x).snd) {
			GO(o, j, go(j, x).snd);
			return;
		}
}

map<int, int> ed[N];

int main() {
#ifdef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	int i, a, b;
	scanf("%d %d", &n, &m);
	for(i = 0; i < m; i++) {
		scanf("%d %d", &a, &b);
		adj[a].pb(b);
		adj[b].pb(a);
	}
	for(i = 1; i <= n; i++)
		if(adj[i].size() == 4) {
			//printf("all.pb(%d)\n", i);
			all.pb(i);
			GO(i, i, go(i, adj[i].front()).snd);
			break;
		}
	deque<int> bad;
	for(int i : all) {
		assert(adj[i].size() == 4);
		for(int j : adj[i]) {
			pii e = go(i, j);
			//printf("%d->%d(%d) is %d\n", i, j, e.snd, e.fst);
			ed[i][e.snd] += e.fst;
		}
		bool bd = false;
		for(int j : adj[i])
			if(ed[i][go(i, j).snd] & 1)
				bd = true;
		//if(bd) printf("bad.pb(%d)\n", i);
		if(bd) bad.pb(i);
	}
	//printf("%d %d\n", all.size(), bad.size());
	bool bp = bip(1, 1);
	if(bp) {
		//puts("Case 1");
		end();
	} else if(bad.empty()) {
		//puts("Case 2");
		keep[all.front()] = 1;
		end();
	} else if(all.size() == bad.size()) {
		//puts("Case 3");
		for(i = 0; i < int(all.size()); i += 2)
			keep[all[i]] = 1;
		end();
	} else {
		//puts("Case 4");
		while(all.back() == bad.back()) {
			all.push_front(all.back());
			bad.push_front(all.back());
			all.pop_back();
			bad.pop_back();
		}
		int ind = 0;
		for(int x : all)
			id[x] = ind++;
		while(!bad.empty()) {
			deque<int> dq;
			dq.push_back(bad.front()); bad.pop_front();
			while(bad.size() > 0 && id[bad.front()] == id[dq.back()] + 1) {
				dq.push_back(bad.front()); bad.pop_front();
			}
			for(i = 1; i < int(dq.size()); i += 2)
				keep[dq[i]] = 1;
		}
		end();
	}
}
