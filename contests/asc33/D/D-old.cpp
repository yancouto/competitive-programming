#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define pb push_back

const int N = 1123;
vector<int> adj[N], adj2[N];
int seen[N];
vector<int> all[N];

int cmp[N], ok[N];

bool dfs(int u) {
	if(u >= 'A' && u <= 'Z' && ok[u] != 2) return false;
	if(seen[u]) return true;
	seen[u] = 2;
	//printf("seen %c = %d\n", u, 2);
	for(int x : all[u])
		for(int v : adj[x]) {
			//printf("%c -> %c [%d]\n", u, cmp[v], seen[cmp[v]]);
			if(seen[cmp[v]] == 2)
				return true;
			else if(!seen[cmp[v]]) {
				if(dfs(cmp[v])) return true;
			}
		}
	for(int x : all[u])
		for(int v : adj2[x])
			if(!seen[cmp[v]] && dfs(cmp[v]))
				return true;
	seen[u] = 1;
	//printf("seen %c = %d\n", u, 1);
	return false;
}

int d[N], low[N], tempo;
int st[N], sn, seen2[N];

int dfs0(int u) {
	d[u] = low[u] = tempo++;
	seen2[u] = 1;
	st[sn++] = u;
	for(int v : adj2[u])
		if(seen2[v])
			low[u] = min(low[u], d[v]);
		else {
			dfs0(v);
			low[u] = min(low[u], low[v]);
		}
	if(low[u] >= d[u]) {
		int a;
		do {
			a = st[--sn];
			cmp[a] = u;
			d[a] = low[a] = INT_MAX;
			all[u].pb(a);
		} while(a != u);
	}
}



char to[N][30];
char from[N];

int main() {
#ifdef ONLINE_JUDGE
	freopen("cyclic.in", "r", stdin);
	freopen("cyclic.out", "w", stdout);
#endif
	int i, j, n;
	scanf("%d", &n);
	for(i = 0; i < n; i++) {
		scanf(" %c%s", &from[i], to[i]);
		if(!to[i][2]) { ok[from[i]] = max(ok[from[i]], 1); continue; }
		bool any = false;
		for(j = 2; to[i][j]; j++)
			any |= (to[i][j] >= 'A' && to[i][j] <= 'Z');
		if(!any) ok[from[i]] = 2;
		//printf("ok[%c] = %d\n", from[i], ok[from[i]]);
		// 0 ruim
		// 1 medio
		// 2 bom
	}
	for(int k = 0; k < 1000; k++)
		for(i = 0; i < n; i++) {
			if(!to[i][2]) continue;
			bool any2 = false, all1 = true, any0 = false;
			for(j = 2; to[i][j]; j++)
				if(to[i][j] >= 'A' && to[i][j] <= 'Z') {
					if(ok[to[i][j]] == 0) any0 = true, all1 = false;
					else if(ok[to[i][j]] == 2) any2 = true, all1 = false;
				} else all1 = false;
			//printf("[%d] %d %d\n", i, any0, any2);
			//if(!any0 && !all1) printf("here %c\n", from[i]);
			if(!any0 && !all1) ok[from[i]] = 2;
			if(!any0) ok[from[i]] = max(ok[from[i]], 1);
		}
	//for(i = 'A'; i <= 'Z'; i++) printf("%c %d\n", i, ok[i]);
	for(i = 0; i < n; i++) {
		if(!to[i][2]) continue;
		if(ok[from[i]] != 2) continue;
		bool any0 = false;
		int ct = 0;
		for(j = 2; to[i][j]; j++)
			if(to[i][j] >= 'A' && to[i][j] <= 'Z') {
				if(ok[to[i][j]] == 0) any0 = true;
				if(ok[to[i][j]] != 1) ct++;
			} else ct++;
		if(any0) continue;
		//printf("ct %d s%s\n", ct, to[i]);

		if(ct == 1) {
			for(j = 2; to[i][j]; j++)
				if((to[i][j] >= 'a' && to[i][j] <= 'z') || ok[to[i][j]] == 2) {
					//printf("adj2 %c -> %c\n", from[i], to[i][j]);
					adj2[from[i]].pb(to[i][j]);
				}
		} else {
			for(j = 2; to[i][j]; j++) {
				//printf("adj %c -> %c\n", from[i], to[i][j]);
				if((to[i][j] >= 'a' && to[i][j] <= 'z') || ok[to[i][j]] == 2)
					adj[from[i]].pb(to[i][j]);
			}
		}
	}
	for(i = 0; i < 256; i++)
		if(!seen2[i])
			dfs0(i);
	if(ok['S'] == 2 && dfs(cmp['S']))
		puts("infinite");
	else
		puts("finite");
}
