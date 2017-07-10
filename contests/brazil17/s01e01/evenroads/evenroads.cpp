#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define fst first
#define snd second
typedef long long ll;
typedef pair<int, int> pii;

typedef pii city;
typedef pair<city, int> pci;

int seen[11234][2];
vector<pci> adj[11234][2];

struct cmp {

bool operator()(pci a, pci b) {
	return a.snd < b.snd;
}

};

int main() {
	int i, n, m, a, b, c;
	scanf("%d %d", &n, &m);
	for(i = 0; i < m; i++) {
		scanf("%d %d %d", &a, &b, &c); a--; b--;
		adj[a][0].pb(pci(city(b, 1), c));
		adj[a][1].pb(pci(city(b, 0), c));
		adj[b][0].pb(pci(city(a, 1), c));
		adj[b][1].pb(pci(city(a, 0), c));
	}
	priority_queue<pci, vector<pci>, cmp> pq;
	pq.push(pci(city(0, 0), 0));
	while(!pq.empty()) {
		pci x = pq.top(); pq.pop();
		city c = x.fst;
		if(seen[c.fst][c.snd]) continue;
		seen[c.fst][c.snd] = 1;
		if(c.fst == n - 1 && c.snd == 0) { printf("%d\n", -x.snd); return 0; }
		for(pci cd : adj[c.fst][c.snd])
			pq.push(pci(cd.fst, x.snd - cd.snd));
	}
	puts("-1");
}
