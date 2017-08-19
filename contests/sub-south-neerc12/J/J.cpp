#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> pii;
#define pb push_back

const int N = 2e5+7;
const int INF = 1e9+7;

int n;
int a[N], b[N], t[N], pr[N];
vector<int> adj[N];
vector<pii> chd;
vector<ll> bst;
int isotm[N];
int me[N];
vector<int> edd;
int deg[N];

ll siz (int fr, int p) {
	int u = a[fr];
	if (p == u)
		u = b[fr];

	ll sz = t[fr];
	for (int ed : adj[u]) {
		if (ed == fr) continue;
		sz = max(sz, siz(ed, u) + t[fr]);
	}
	return sz;
}

ll dp (int fr, int p, int h) {
	h -= t[fr];
	int u = a[fr];
	if (p == u)
		u = b[fr];

	if (adj[u].size() == 1 && h == 0) {
		return me[fr] = pr[fr];
	}
	
	ll rs = pr[fr];
	ll ot = 0;
	for (int ed : adj[u]) {
		if (ed == fr) continue;
		ot += dp(ed, u, h);
	}

	return me[fr] = min(rs, ot);
}

void build (int fr, int p, int h) {
	h -= t[fr];
	int u = a[fr];
	if (p == u)
		u = b[fr];

	if (adj[u].size() == 1 && h == 0) {
		edd.pb(fr);
		return;
	}
	if (me[fr] == 0) return;
	
	if (me[fr] == pr[fr]) {
		edd.pb(fr);
		return;
	} else {
		for (int ed : adj[u]) {
			if (ed == fr) continue;
			build(ed, u, h);
		}
	}
}

int main() {
#ifdef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif

	scanf("%d", &n);

	for (int i = 0; i < n-1; i++) {
		scanf("%d %d %d %d", a+i, b+i, t+i, pr+i);
		a[i]--; b[i]--;
		adj[a[i]].pb(i);
		adj[b[i]].pb(i);
	}

	if (n == 2) {
		printf("%d\n1\n1\n", pr[0]);
		return 0;
	}

	priority_queue<pii> qu;
	for (int i = 0; i < n; i++)
		if (adj[i].size() == 1)
			qu.push(pii(-0,i));

	int cnt = 0;
	while (!qu.empty()) {
		pii att = qu.top();
		qu.pop();
		int u = att.second;
		cnt = u;

		for (int ed : adj[u]) {
			int v = a[ed];
			if (v == u)
				v = b[ed];
			deg[v]++;

			if (deg[v] + 1 == adj[v].size())
				qu.push(pii(att.first - t[ed], v));
		}
	}

	ll mx = 0;
	for (int ed : adj[cnt]) {
		ll sz = siz(ed,cnt);
		chd.pb(pii(sz, ed));
		mx = max(mx, sz);
	}

	ll snd = 0;

	ll res = 0;
	ll ign = 0;
	int cont = 0;
	int iggg = -1;

	for (pii elm : chd) {
		if (elm.first == mx) {
			cont++;
			ll cur = dp(elm.second, cnt, mx);

			if (cur >= ign) {
				res += ign;
				ign = cur;
				if (iggg != -1) {
					isotm[iggg] = 1;
				}
				iggg = elm.second;
			} else {
				isotm[elm.second] = 1;
				res += cur;
			}
		} else {
			snd = max(snd, elm.first);
		}
	}

	if (cont > 1) {
		for (int i = 0; i < n-1; i++)
			if (isotm[i])
				build(i, cnt, mx);
		printf("%lld\n", res);
	} else {
		ll sum = 0;
		for (pii elm : chd) {
			if (elm.first == snd) {
				sum += dp(elm.second, cnt, snd);
			}
		}

		if (sum < ign) {
			for (pii elm : chd)
				if (elm.first == snd)
					build(elm.second, cnt, snd);
		} else {
			build(iggg, cnt, mx);
		}

		printf("%lld\n", min(sum, ign));
	}

	printf("%d\n", (int) edd.size());
	for (int i : edd)
		printf("%d ", i+1);
	printf("\n");
}
