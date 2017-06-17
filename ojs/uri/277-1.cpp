#include <bits/stdc++.h>
using namespace std;

#define pb push_back
const int N = 112345;
vector<int> adj[N];
int has[N], a[N], p[N];

int go(int u) {
	if(!has[u]) return 0;
	int ct = has[u];
	for(int v : adj[u])
		ct += go(v);
	return ct;
}

int main() {
	int i, n, r, j, s, c;
	scanf("%d", &n);
	for(i = 0; i < n; i++) {
		scanf("%d", &p[i]); p[i]--;
		if(p[i] != i) adj[p[i]].pb(i);
		else r = i;
	}
	scanf("%d %d", &s, &c);
	for(i = 0; i < s; i++) {
		for(j = 0; j < c; j++) {
			scanf("%d", &a[j]); a[j]--;
			has[a[j]]++;
		}
		if(go(r) == c) puts("yes");
		else puts("no");
		for(j = 0; j < c; j++) has[a[j]]--;
	}
}
