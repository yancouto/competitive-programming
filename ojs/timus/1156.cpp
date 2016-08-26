#include <bits/stdc++.h>
using namespace std;
#define pb push_back

void imp() {
	puts("IMPOSSIBLE");
	exit(0);
}

vector<int> adj[102];
int color[102], seen[102], t, w[2];
void dfs(int u, int c) {
	if(seen[u] && (color[u] & 1) != c) imp();
	if(seen[u]) return;
	seen[u] = true;
	color[u] = t + c;
	w[c]++;
	for(int v : adj[u])
		dfs(v, !c);
}

int a[102][2]; int sz, n;
int memo[102][52][52];
bool solve(int i, int l, int r) {
	if(l > n || r > n) return false;
	if(i == sz) return l == n && r == n;
	int &x = memo[i][l][r];
	if(x != -1) return x;
	x = solve(i + 1, l + a[i][0], r + a[i][1]) | solve(i + 1, l + a[i][1], r + a[i][0]);
	return x;
}

int b[2][52], bn[2];
void build(int i, int l, int r) {
	if(i == sz) return;
	int ga = 0;
	if(solve(i + 1, l + a[i][1], r + a[i][0])) ga = 1;
	for(int j = 0; j < 2 * n; j++)
		if(color[j] == 2 * i || color[j] == 2 * i + 1) {
			b[ga != (color[j] & 1)][bn[ga != (color[j] & 1)]++] = j;
		}
	build(i + 1, l + a[i][ga], r + a[i][!ga]);
}

int main() {
	int i, j, m, a, b;
	scanf("%d %d", &n, &m);
	for(i = 0; i < m; i++) {
		scanf("%d %d", &a, &b); a--; b--;
		adj[a].pb(b); adj[b].pb(a);
	}
	for(i = 0; i < 2*n; i++)
		if(!seen[i]) {
			w[0] = w[1] = 0;			
			dfs(i, 0);
			::a[sz][0] = w[0]; ::a[sz++][1] = w[1];
			t += 2;
		}
	memset(memo, -1, sizeof memo);
	if(!solve(0, 0, 0)) imp();
	build(0, 0, 0);	
	for(i = 0; i < n - 1; i++) printf("%d ", ::b[0][i] + 1);
	printf("%d\n", ::b[0][n - 1] + 1);
	for(i = 0; i < n - 1; i++) printf("%d ", ::b[1][i] + 1);
	printf("%d\n", ::b[1][n - 1] + 1);
}
