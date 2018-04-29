#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<int, ll> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }

const int N = 1123;
int a[N], r1[N], r2[N];
ll has[N];
ll nd[N];

struct cmp {
	bool operator() (int i, int j) { if(nd[i] != nd[j]) return nd[i] > nd[j]; else return i < j; }
};

int m;
bool can(ll x) {
	//printf("\n==== CAN %lld? ====\n", x);
	for(int i = 0; i < m; i++)
		has[i] = a[i], nd[i] = 0;
	set<int, cmp> need;
	nd[0] = x;
	need.insert(0);
	int ct = 0;
	ll tot = 0;
	while(!need.empty()) {
		if(ct++ > .5e5) return false;
		int i = *need.begin(); need.erase(need.begin());
		//printf("%d needs %lld\n", i, nd[i]);
		tot += nd[i];
		if(tot > 1e12) return false;
		ll g = min(nd[i], has[i]);
		has[i] -= g;
		g = nd[i] - g;
		nd[i] = 0;
		if(g > 0) {
			//printf("need %lld of %d from %d + %d\n", g, i, r1[i], r2[i]);
			need.erase(r1[i]); need.erase(r2[i]);
			nd[r1[i]] += g; nd[r2[i]] += g;
			need.insert(r1[i]); need.insert(r2[i]);
		}
	}
	return true;
}

int main() {
	for_tests(tn, tt) {
		int i;
		scanf("%d", &m);
		//for(i = 0; i < m; i++) r1[i] = rand() % m, r2[i] = rand() % m;
		//for(i = 0; i < m; i++) a[i] = (rand() % 500000000) + 500000000;
		//a[0] = 0;
		for(i = 0; i < m; i++) scanf("%d %d", &r1[i], &r2[i]), r1[i]--, r2[i]--;
		for(i = 0; i < m; i++) scanf("%d", &a[i]);
		ll l = 0, r = 1e12;
		while(l < r) {
			ll m = (l + r + 1) / 2;
			if(can(m)) l = m;
			else r = m - 1;
		}
		printf("Case #%d: %lld\n", tt, l);

	}
}
