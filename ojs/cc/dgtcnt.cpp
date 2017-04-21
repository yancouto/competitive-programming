#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)

ll fat[20], p10[20];
int a[12];
ll L, R;
char l[112], r[112];

inline ll choose(ll n, ll p) {
	if(p > n) return 0;
	return (fat[n] / fat[p]) / fat[n - p];
}

ll go(int i, bool pl, bool pr, bool l0, int bm) {
	//printf("go(%d, %d, %d, %d, %d)\n", i, pl, pr, l0, bm);
	if(!pl && !pr) {
		int all = 0;
		for(int d = 0; d <= 9; d++)
			if((bm >> d) & 1)
				all += a[d];
		ll ans = fat[all] * choose(19 - i, all);
		for(int d = 0; d <= 9; d++)
			if((bm >> d) & 1)
				ans /= fat[a[d]];
		ll ot = 10 - __builtin_popcount(bm);
		for(int d = 0; d < 19 - i - all; d++)
			ans *= ot;
		//printf("= %lld\n", ans);
		return ans;
	}
	if(!l[i]) {
		int all = 0;
		for(int d = 0; d <= 9; d++)
			if((bm >> d) & 1)
				all += a[d];
		return all == 0;
	}
	ll tot = 0;
	for(int d = 0; d <= 9; d++) {
		if(pl && d < l[i] - '0') continue;
		if(pr && d > r[i] - '0') continue;
		if((d || !l0) && ((bm >> d) & 1) && !a[d]) continue;
		if((d || !l0) && ((bm >> d) & 1)) a[d]--;
		tot += go(i + 1, pl && d == l[i] - '0', pr && d == r[i] - '0', l0 && d == 0, bm);
		if((d || !l0) && ((bm >> d) & 1)) a[d]++;
	}
	return tot;
}

int main() {
	fat[0] = p10[0] = 1;
	for(ll i = 1; i < 20; i++)
		fat[i] = i * fat[i - 1],
		p10[i] = 10ll * p10[i - 1];
	for_tests(tn, tt) {
		scanf("%lld %lld", &L, &R);
		sprintf(l, "%019lld", L);
		sprintf(r, "%019lld", R);
		//printf("%s vs\n%s\n", l, r);
		for(int i = 0; i < 10; i++) scanf("%d", &a[i]);
		ll tot = 0;
		for(int i = 0; i < (1 << 10); i++) {
			int all = 0;
			for(int j = 0; j < 10; j++)
				if((i >> j) & 1)
					all += a[j];
			if(all > 19) continue;
			ll v = go(0, true, true, true, i);
			//printf("%s: %lld\n", bitset<10>(i).to_string().c_str(), v);
			if((__builtin_popcount(i)) & 1) tot -= v;
			else tot += v;
		}
		printf("%lld\n", tot);
	}
}
