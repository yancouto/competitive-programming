#include <bits/stdc++.h>
using namespace std;
#define pb push_back

const int N = 1123;
int seen[N][N], seen2[N], S[N];
vector<int> adj[N], adj2[N];

void go(int i, int j) {
	if(seen[j][i]) return;
	seen[j][i] = 1;
	for(int v : adj2[i])
		go(v, j);
}

bool dfs(int u) {
	seen2[u] = 2;
	//printf("at %c with 2\n", u);
	for(int v : adj[u]) {
		//printf("%c -> %c\n", u, S[v]);
		if(seen2[S[v]] == 2) return true;
		else if(seen2[S[v]] == 0 && dfs(S[v])) return true;
	}
	for(int v : adj2[u])
		if(seen2[S[v]] == 0 && dfs(S[v]))
			return true;
	seen2[u] = 1;
	//printf("at %c with 1\n", u);
	return false;
}

char to[N];

int main() {
#ifdef ONLINE_JUDGE
	freopen("cyclic.in", "r", stdin);
	freopen("cyclic.out", "w", stdout);
#endif
	int i, n, j;
	char from;
	scanf("%d", &n);
	for(i = 0; i < n; i++) {
		scanf(" %c %s", &from, to);
		if(!to[2]) continue;
		if(!to[3]) adj2[from].pb(to[2]);
		else
			for(j = 2; to[j]; j++)
				adj[from].pb(to[j]);
	}

	for(i = 0; i < 256; i++)
		go(i, i);
	for(i = 0; i < 256; i++) S[i] = i;
	for(i = 0; i < 256; i++)
		for(j = i + 1; j < 256; j++)
			if(seen[i][j] && seen[j][i] && S[j] == j) {
				//printf("join(%d, %d)\n", i, j);
				S[j] = i;
				for(int v : adj[j]) adj[i].pb(v);
				for(int v : adj2[j]) adj2[i].pb(v);
			}
	if(dfs(S['S'])) puts("infinite");
	else puts("finite");
}
