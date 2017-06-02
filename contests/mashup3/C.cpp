#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define left asd

const int N = 212345;
vector<int> adj[N];
int d[N], cd[N], left[N];


int main() {
	int i, n, m, x, l, a, b;
	scanf("%d %d %d %d", &n, &m, &x, &l); x--; l--;
	for(i = 0; i < m; i++) {
		scanf("%d %d", &a, &b); a--; b--;
		adj[a].pb(b);
		adj[b].pb(a);
		d[a]++; d[b]++;
	}
	for(i = 0; i < n; i++) cd[i] = d[i];
	queue<int> q;
	q.push(l); left[l] = true;
	while(!q.empty()) {
		int u = q.front(); q.pop();
		for(int v : adj[u]) {
			cd[v]--;
			if(cd[v] <= d[v] / 2 && !left[v]) q.push(v), left[v] = true;
		}
	}
	if(left[x]) puts("leave");
	else puts("stay");
}
