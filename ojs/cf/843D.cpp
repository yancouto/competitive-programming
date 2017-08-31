#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<ll, int> pii;
#define pb push_back
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }
#ifdef ONLINE_JUDGE
#	define debug(args...) {}
#else
#	define debug(args...) fprintf(stderr, args)
#endif

template<class num> inline void rd(num &x) {
	char c;
	while(isspace(c = getchar()));
	bool neg = false;
	if(!isdigit(c)) neg = (c == '-'), x = 0;
	else x = c - '0';
	while(isdigit(c = getchar()))
		x = (x << 3) + (x << 1) + c - '0';
	if(neg) x = -x;
}

int n;

const int N = 112345;
vector<int> adj[N];
int v[N], op[N], b[N], c[N], seen[N];
ll d[N], ans[N];
vector<int> rm[N];

int main() {
	int i, q, n, m, a, x;
	rd(n); rd(m); rd(q);
	for(i = 0; i < m; i++) {
		rd(a); rd(b[i]); rd(c[i]);
		adj[a].pb(i);
	}
	for(i = 0; i < q; i++) {
		rd(op[i]);
		if(op[i] == 1) {
			rd(v[i]);
		} else {
			int qt;
			rd(qt);
			while(qt--) {
				rd(x);
				rm[i].pb(x - 1);
				c[x - 1]++;
			}
		}
	}
	priority_queue<pii> pq;
	pq.push(pii(0, 1));
	for(i = 1; i <= n; i++) d[i] = LLONG_MAX, seen[i] = INT_MAX;
	vector<deque<int>> all;
	while(!pq.empty()) {
		pii x = pq.top(); pq.pop();
		if(d[x.snd] != LLONG_MAX) continue;
		d[x.snd] = -x.fst;
		add(all, x.snd);
		for(int e : adj[x.snd])
			pq.push(pii(x.fst - c[e], b[e]));
	}
	//for(i = 1; i <= n; i++) printf("d[%d] = %lld\n", i, d[i]);
	int oq = q;
	while(q--) {
		if(op[q] == 1) {
			ans[q] = d[v[q]];
		} else {
			for(int e : rm[q])
				c[e]--;
			vector<deque<int>> all2;
			for(deque<int> &dq : all) {
				while(!dq.empty()) {
					int x = dq.front(); dq.pop_front();
					if(seen[x] == q) continue;
					for(int e : adj[x])
				}
			}
			queue<int> qq;
			qq.push(1); seen[1] = q;
			while(!qq.empty()) {
				int x = qq.front(); qq.pop();
				for(int e : adj[x])
					if(d[x] + c[e] < d[b[e]] || (seen[b[e]] != q && d[x] + c[e] == d[b[e]])) {
						//printf("%d[%lld] -%d> %d[%lld]\n", x, d[x], c[e], b[e], d[b[e]]);
						d[b[e]] = d[x] + c[e];
						seen[b[e]] = q;
						qq.push(b[e]);
					}
			}
			//for(i = 1; i <= n; i++) printf("d[%d] = %lld\n", i, d[i]);
		}
	}
	for(i = 0; i < oq; i++)
		if(op[i] == 1) {
			if(ans[i] == LLONG_MAX) puts("-1");
			else printf("%lld\n", ans[i]);
		}
}
