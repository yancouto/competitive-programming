#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> pii;
#define pb push_back
#define fst first
#define snd second

const int N = 112345;

vector<pii> adj[N];
int p[N], d[N], mrk[N], d2[N];

int main() {
	int i, n, m, k, a, b, c;
	scanf("%d %d %d", &n, &m, &k);
	for(i = 0; i < k; i++) scanf("%d", &p[i]);
	for(i = 0; i < m; i++) {
		scanf("%d %d %d", &a, &b, &c);
		adj[a].pb(pii(b, c));
		adj[b].pb(pii(a, c));
	}
	for(i = 1; i <= n; i++) d[i] = d2[i] = INT_MAX;
	int best = 0;
	for(i = 1; i < k; i++) {
		int mn = INT_MAX;
		int j = 0;
		for(pii e : adj[p[i - 1]]) {
			if(e.fst == p[i]) {
				if(mn > e.snd) {
					mrk[p[i - 1]] = j;
					mn = e.snd;
				}
			}
			j++;
		}
		best += mn;
	}
	priority_queue<pii> pq;
	pq.push(pii(0, 1));
	while(!pq.empty()) {
		pii x = pq.top(); pq.pop();
		if(d[x.snd] != INT_MAX) continue;
		d[x.snd] = -x.fst;
		for(pii e : adj[x.snd])
			pq.push(pii(x.fst - e.snd, e.fst));
	}
	pq.push(pii(0, n));
	while(!pq.empty()) {
		pii x = pq.top(); pq.pop();
		if(d2[x.snd] != INT_MAX) continue;
		d2[x.snd] = -x.fst;
		for(pii e : adj[x.snd])
			pq.push(pii(x.fst - e.snd, e.fst));
	}
	for(i = 1; i <= n; i++) {
		if(d[i] == INT_MAX) continue;
		int j = 0;
		for(pii e : adj[i]) {
			if(j == mrk[i]) { j++; continue; }
			if(d[e.fst] != INT_MAX && d2[e.fst] != INT_MAX && d[i] + e.snd + d2[e.fst] == best) {
				puts("yes");
				return 0;
			}
			j++;
		}
	}
	puts("no");
}
