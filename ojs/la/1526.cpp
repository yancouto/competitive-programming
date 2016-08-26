#include <bits/stdc++.h>
using namespace std;
#define x first
#define y second
typedef unsigned long long ull;
typedef long long ll;
typedef pair<ll, ll> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
template<typename T> inline T abs(T t) { return t < 0? -t : t; }
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }

vector<pii> v[200009];
int main() {
	int i, n, x, y, z;
	ll m;
	while(scanf("%d %lld", &n, &m) != EOF && (n || m)) {
		for(i = 0; i < n; i++) {
			scanf("%d %d %d", &x, &y, &z);
			v[z - 1].pb(pii(x, -y));
		}
		set<pii> s;
		s.insert(pii(0, -2000000));
		s.insert(pii(2000000, 0));
		ll tot = 0;
		ll ar = 0;
		for(i = m + 3; i >= 0; i--) {
			while(!v[i].empty()) {
				pii p = v[i].back(); v[i].pop_back();
				if(*s.lower_bound(p) == p) continue;
				if(-s.upper_bound(p)->y >= -p.y) continue;
				auto it = s.insert(p).first;
				ar += (p.x - prev(it)->x) * (-p.y + next(it)->y);
				while(-prev(it)->y <= -p.y) {
					auto e = prev(it);
					ar += (e->x - prev(e)->x) * (-p.y + e->y);
					s.erase(e);
				}
			}
			tot += ar;
		}
		printf("%lld\n", m * m * m - tot);
	}
}
