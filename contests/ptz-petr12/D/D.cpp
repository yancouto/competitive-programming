#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define pb push_back
typedef pair<int, int> pii;

const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }

int na, nb;
#define fst first
#define snd second
char a[112], b[112];

map<vector<pii>, ll> mp;
ll go(const vector<pii> &v) {
	if(v.empty()) return 0;
	if(v.front().fst == na && v.front().snd == nb) return 1;
	if(mp.count(v)) return mp[v];
	ll &ans = mp[v];
	ans = 0;
	for(int i = 0; i <= 1; i++) {
		vector<pii> x;
		for(pii p : v) {
			if(p.fst < na && a[p.fst] - '0' == i) x.pb(pii(p.fst + 1, p.snd));
			if(p.snd < nb && b[p.snd] - '0' == i) x.pb(pii(p.fst, p.snd + 1));
		}
		sort(x.begin(), x.end());
		x.erase(unique(x.begin(), x.end()), x.end());
		ans = mod(ans + go(x));
	}
	return ans;
}

int main () {
#ifdef ONLINE_JUDGE
	freopen("interleave.in", "r", stdin);
	freopen("interleave.out", "w", stdout);
#endif
	//na = (rand() % 50) + 1;
	//nb = (rand() % 50) + 1;
	//for(int i = 0; i < na; i++) a[i] = (rand() % 2) + '0';
	//for(int i = 0; i < nb; i++) b[i] = (rand() % 2) + '0';
	scanf("%s %s", a, b);
	na = strlen(a);
	nb = strlen(b);
	vector<pii> v; v.pb(pii(0, 0));
	printf("%lld\n", go(v));
}
