#include <bits/stdc++.h>
using namespace std;
#define pb push_back
typedef long long ll;
typedef pair<int, int> pii;

const int M = 100009;
vector<int> adj[M];
int seen[M], tempo, val[M];
int vval;

void dfs(int u) {
	seen[u] = tempo;
	for(int v : adj[u])
		if(seen[v] != tempo)
			dfs(v);
	val[u] = vval--;
}

int p;
int x[M], pos[M];

bool ok(int n, bool prn=false) {
	if(n == 0) {
		if(prn) puts("");
		return true;
	}
	for(int i = 0; i <= n; i++) adj[i].clear();
	for(int j = 0; j < p; j++)
		for(int i = x[j]; i <= n; i++) {
			if(pos[j]) adj[i - x[j]].pb(i);
			else adj[i].pb(i - x[j]);
		}
	vval = n;
	tempo++;
	for(int i = 0; i <= n; i++)
		if(seen[i] != tempo)
			dfs(i);
	//if(n <= 10) for(int i = 0; i <= n; i++) printf("val[%d] = %d\n", i, val[i]);
	for(int i = 0; i <= n; i++)
		for(int j : adj[i])
			if(val[j] < val[i])
				return false;
	if(prn) {
		for(int i = 1; i <= n; i++)
			printf("%d%c", val[i] - val[i - 1], " \n"[i == n]);
	}
	return true;
}

char s[123];

int main() {
	int i;
	scanf("%d", &p);
	for(i = 0; i < p; i++) {
		scanf("%d %s", &x[i], s);
		pos[i] = (s[0] == 'p');
	}
	for(i = 1; i < p; i++)
		if(pos[i] != pos[0])
			break;
	if(i == p) { puts("-1"); return 0; }
	int l = 0, r = M;
	while(l < r) {
		int m = (l + r + 1) / 2;
		if(ok(m)) l = m;
		else r = m - 1;
	}
	printf("%d\n", l);
	ok(l, 1);
}
