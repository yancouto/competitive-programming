#include <bits/stdc++.h>
using namespace std;

#define pb push_back
typedef long long ll;
typedef pair<ll, ll> pii;
#define fst first
#define snd second

void clean(vector<pii> &v) {
	sort(v.begin(), v.end());
	vector<pii> v2 = v;
	v.clear();
	for(pii p : v2) {
		if(v.empty() || v.back().fst != p.fst)
			v.pb(p);
	}
}

ll mna = LLONG_MAX;

vector<pii> L, R;

void go(ll bm, ll S, pii l) {
	if((S >> 40) < l.fst) return;
	S -= (l.fst << 40);
	auto it = lower_bound(R.begin(), R.end(), pii(S, LLONG_MIN));
	if(it != R.end() && it->fst == S)
		mna = min(mna, (l.snd << 40) + (bm << 20) + (it->snd));
}

ll ct[100];
ll a[112345];
int n; ll S;
void check() {
	for(int i = 0; i < n; i++) printf("%lld%c", a[i], " \n"[i == n - 1]);
	printf("a = %lld\n", mna);
	ll tot = 0;
	for(int i = 0; i < n; i++) {
		tot += a[i] ^ mna;
		assert(tot <= S);
	}
	assert(tot == S);
}

int main() {
	int i, j; ll x;
	n = 10;
	while(true) {
		//for(i = 0; i < n; i++) a[i] = ll(rand()) ^ (ll(rand()) << 20);
		//S = accumulate(a, a + n, 0ll);
		//ll gen_a = rand();
		//printf("gen with %lld S %lld\n", gen_a, S);
		//for(i = 0; i < n; i++)
		//	a[i] ^= gen_a;
		L.clear(); R.clear();
		mna = LLONG_MAX;
		for(i = 0; i < 60; i++) ct[i] = 0;
		scanf("%d %lld", &n, &S);
		for(i = 0; i < n; i++) {
			scanf("%lld", &x); a[i] = x;
			x = a[i];
			for(j = 0; j < 60; j++)
				if((x >> j) & 1)
					;
				else
					ct[j]++;
		}
		for(i = 0; i < (1 << 20); i++) {
			ll tot = 0;
			for(j = 0; j < 20; j++)
				if((i >> j) & 1)
					tot += (1ll << j) * ct[j];
				else
					tot += (1ll << j) * ll(n - ct[j]);
			R.pb(pii(tot, i));
			tot = 0;
			for(j = 0; j < 20; j++)
				if((i >> j) & 1)
					tot += (1ll << j) * ct[j + 40];
				else
					tot += (1ll << j) * ll(n - ct[j + 40]);
			L.pb(pii(tot, i));
		}
		clean(L);
		clean(R);
		for(i = 0; i < (1 << 20); i++) {
			ll tot = 0;
			for(j = 0; j < 20; j++)
				if((i >> j) & 1)
					tot += (1ll << (j + 20)) * ct[j + 20];
				else
					tot += (1ll << (j + 20)) * ll(n - ct[j + 20]);
			ll xS = S - tot;
			if(xS < 0) continue;
			auto it = upper_bound(L.begin(), L.end(), pii((xS >> 40), LLONG_MAX));
			if(it != L.end()) go(i, xS, *it);
			if(it != L.end() && next(it) != L.end()) go(i, xS, *next(it));
			if(it != L.begin()) go(i, xS, *prev(it));
			if(it != L.begin() && prev(it) != L.begin()) go(i, xS, *prev(prev(it)));
		}
		if(mna == LLONG_MAX) mna = -1;
		//else check();
		printf("%lld\n", mna);
		break;
	}
}
