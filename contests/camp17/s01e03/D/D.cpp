#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<int, ll> pii;
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

const int N = 112345;
int n;

struct no {
	int u, from; ll d;
	no() {}
	no(int u, ll d, int f) : u(u), d(d), from(f) {}
	bool operator < (no o) const { return d > o.d; }
};

ll d[N];
int from[N], seen[N];
vector<pii> adj[N];

int main() {
	int i, j, s;
	int p, n, m, a, b, c;
	rd(p); rd(n); rd(m);

	priority_queue<no> pq;
	for(i = 0; i < p; i++) rd(s), pq.push(no(s-1, 0, i));
	for(i = 0; i < m; i++) {
		rd(a); rd(b); rd(c); a--; b--; c *= 6;
		adj[a].pb(pii(b, c));
		adj[b].pb(pii(a, c));
	}
	ll mn = LLONG_MAX;
	while(!pq.empty()) {
		no x = pq.top(); pq.pop();
		if(seen[x.u]) {
			// coisas
			if(from[x.u] != x.from)
				mn = min(mn, x.d + d[x.u]);
			continue;
		}
		seen[x.u] = true;
		d[x.u] = x.d;
		from[x.u] = x.from;
		for(pii e : adj[x.u]) {
			if(seen[e.fst]) {
				if(from[e.fst] == x.from) continue;
				mn = min(mn, (e.snd - (x.d - d[e.fst])) / 2 + x.d);
			} else pq.push(no(e.fst, x.d + e.snd, x.from));
		}
	}
	printf("%d\n", mn);
}
