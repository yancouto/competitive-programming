#include <bits/stdc++.h>
#define cout if (1) cout

using namespace std;
typedef long long int ll;
typedef pair<ll,ll> pii;
#define pb push_back

const int N = 5123;

ll c[N], s[N];
vector<int> adj[N];
int p[N];

void simul(int u) {
	ll x = min(s[u], c[u]);
	s[u] -= x;
	s[p[u]] += x;
	for(int v : adj[u])
		simul(v);
}

vector<pii> go(int u) {
	vector<pii> evs;
	ll cur_time = 0, cur_supply = 0, cur_stock = s[u];
	ll cur_speed = c[u];
	for(int v : adj[u]) {
		cur_supply += c[v];
		vector<pii> evv = go(v);
		for(pii ev : evv) evs.pb(ev);
	}
	vector<pii> my_evs;
	sort(evs.begin(), evs.end());
	for(pii ev : evs) {
		ll nx_time = ev.first;
		ll supply_drop = ev.second;
		if(nx_time == cur_time) {
			cur_supply -= supply_drop;
			continue;
		}
		while(cur_stock + (nx_time - cur_time - 1) * cur_supply < (nx_time - cur_time) * cur_speed) {
			ll mn;
			if(cur_speed == cur_supply)
				mn = 0;
			else
				mn = (cur_stock - cur_supply + (cur_speed - cur_supply - 1)) / (cur_speed - cur_supply);
			//assert(mn >= 0 && cur_time + mn < nx_time);
			ll old_speed = cur_speed;
			cur_speed = cur_stock + mn * cur_supply - mn * cur_speed;
			cur_stock = cur_speed;
			my_evs.pb(pii(cur_time + mn, old_speed - cur_speed));
			cur_time += mn;
		}
		cur_stock += (nx_time - cur_time) * cur_supply;
		cur_time = nx_time;
		cur_supply -= supply_drop;
	}
	//assert(cur_supply == 0);
	if(cur_speed) {
		ll mn = (cur_stock / cur_speed);
		ll old_speed = cur_speed;
		cur_speed = cur_stock % cur_speed;
		my_evs.pb(pii(cur_time + mn, old_speed - cur_speed));
		if(cur_speed)
			my_evs.pb(pii(cur_time + mn + 1, cur_speed));
		//printf("%d: c %lld s %lld\n", u, c[u], s[u]);
		//for(pii ev : my_evs) printf("(%lld, %lld) ", ev.first, ev.second);
		//printf("\n======\n");
	}
	return my_evs;
}

int main() {
	int t;
	scanf("%d", &t);
	while(t--) {
		int i, n;
		scanf("%d", &n);
		for(i = 1; i <= n; i++) adj[i].clear();
		for(i = 2; i <= n; i++)
			scanf("%lld", &s[i]);
		for(i = 2; i <= n; i++) {
			scanf("%d", &p[i]);
			adj[p[i]].pb(i);
		}
		for(i = 2; i <= n; i++)
			scanf("%lld", &c[i]);
		for(i = 2; i <= n && s[i] == 0; i++);
		if(i == n + 1) { puts("0"); continue; }
		int k;
		for(k = 1; k <= n + 2; k++) {
			for(int v : adj[1])
				simul(v);
			for(i = 2; i <= n && s[i] == 0; i++);
			if(i == n + 1) { printf("%d\n", k); break; }
		}
		if(k <= n + 2) continue;
		ll tm = 0;
		for(int v : adj[1]) {
			vector<pii> evs = go(v);
			tm = max(tm, evs.back().first);
		}
		printf("%lld\n", tm + n + 2);
	}
}
