#include <bits/stdc++.h>
using namespace std;

#define pb push_back
typedef long long ll;
typedef pair<ll, ll> pii;

int tempo;

struct st {
	int u;
	int ad;
};

const int N = 112345;
int seen[N], d[N];
vector<int> adj[N];

int solve(int a, int b) {
	if(a == b) return 0;
	tempo += 2;
	queue<st> q;
	q.push(st{a, 0});
	q.push(st{b, 1});
	seen[a] = tempo;
	seen[b] = tempo + 1;
	d[a] = d[b] = 0;
	while(!q.empty()) {
		st x = q.front(); q.pop();
		for(int v : adj[x.u]) {
			if(seen[v] == tempo + x.ad) continue;
			if(seen[v] == tempo + !x.ad) {
				return d[x.u] + 1 + d[v];
			}
			seen[v] = tempo + x.ad;
			d[v] = d[x.u] + 1;
			q.push(st{v, x.ad});
		}
	}
	return -1;
}

int S[N], sz[N];
int find(int i) {
	if(S[S[i]] != S[i]) S[i] = find(S[i]);
	return S[i];
}
inline void join(int a, int b) {
	if((a = find(a)) == (b = find(b))) return;
	if(sz[a] < sz[b]) swap(a, b);
	S[b] = a;
	sz[a] += sz[b];
}

int main() {
	int i, n, m, a, b, q;
	scanf("%d %d", &n, &m);
	for(i = 0; i < n; i++) S[i] = i, sz[i] = 1;
	for(i = 0; i < m; i++) {
		scanf("%d %d", &a, &b);
		adj[a].pb(b);
		adj[b].pb(a);
		join(a, b);
	}
	scanf("%d", &q);
	for(i = 0; i < q; i++) {
		scanf("%d %d", &a, &b);
		if(find(a) != find(b)) puts("-1");
		else printf("%d\n", solve(a, b));
	}
}
