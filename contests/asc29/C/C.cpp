#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> pii;

#define pb push_back
#define fst first
#define snd second

typedef double dbl;
const dbl eps = 1e-9;

const int N = 112345;
int ed[N], a[N], b[N], c[N], v[N];
double d[N];
int seen[N], tempo;
vector<pii> adj[N];


int main() {
#ifdef ONLINE_JUDGE
	freopen("lateagain.in", "r", stdin);
	freopen("lateagain.out", "w", stdout);
#endif
	int i, n, m;
	scanf("%d %d", &n, &m);
	for(i = 0; i < m; i++) {
		scanf("%d %d %d", &a[i], &b[i], &c[i]);
		adj[a[i]].pb(pii(b[i], i));
		adj[b[i]].pb(pii(a[i], i));
		v[i] = +1;
	}
	int pt;
	scanf("%d", &pt);
	for(i = 0; i < pt; i++) {
		scanf("%d", &ed[i]);
		v[--ed[i]] = -1;
	}
	dbl l = 0, r = 10000.;
	int its = 100;
	while(its--) {
		dbl m = (l + r) / 2.;
		typedef pair<dbl, int> pdi;
		priority_queue<pdi> pq;
		pq.push(pdi(0, 1));
		tempo++;
		while(!pq.empty()) {
			pdi x = pq.top(); pq.pop();
			if(seen[x.snd] == tempo) continue;
			seen[x.snd] = tempo;
			d[x.snd] = -x.fst;
			for(pii e : adj[x.snd])
				pq.push(pdi(x.fst - max(1., c[e.snd] + v[e.snd] * m), e.fst));
		}
		dbl tot = 0;
		for(i = 0; i < pt; i++)
			tot += max(1., c[ed[i]] - m);
		if(tot <= d[n]) r = m;
		else l = m;
	}
	printf("%.20f\n", l);
	for(i = 0; i < m; i++)
		printf("%.20f%c", max(1., c[i] + v[i] * l), " \n"[i == m - 1]);
}
