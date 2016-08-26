#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef unsigned long long ull;
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }
#ifdef ONLINE_JUDGE
#	define LLD "%I64d"
#	define debug(args...) {}
#else
#	define LLD "%lld"
#	define debug(args...) fprintf(stderr, args)
#endif

ll a[1123];

int n;
void distr(ll x, int r, ll t=1) {
	debug("distr %lld to %d\n", x, r);
	assert(x >= n);
	for(int i = 0; i < n; i++)
		a[i] += t, x--;
	a[r] += x * t;
}

void end() {
	for(int i = 0; i < n; i++)
		printf(LLD" ", a[i]);
	putchar('\n');
	exit(0);
}

void deb() {
	for(int i = 0; i < n; i++)
		debug(LLD " ", a[i]);
	putchar('\n');
}

int main() {
#ifdef ONLINE_JUDGE
	freopen("coins.in", "r", stdin);
	freopen("coins.out", "w", stdout);
#endif
	int i, j, d; ll m;
	scanf("%d" LLD "%d", &n, &m, &d);
	ll tm = m / ll(d);
	i = ((tm) % n);
	ll all = ll(m) / d + 1ll;
	debug("tm %lld all %lld\n", tm, all);
	ll md = m % d;
	debug("i %d\n", i);
	if(md >= n) {
		debug("INITIAL\n");
		distr(md, i);
		md = 0;
	}
	all--;
	while(md < n && all > 0) {
		md += d;
		i = i - 1;
		if(i == -1) i = n - 1;
		all--;
	}
	deb();
	debug("all = %lld first greater md %lld i %d\n", all, md, i);
	distr(md, i); md = 0;
	if(!all) end();
	ll cyc = ll(n + d - 1ll) / d;
	debug("cyc %lld\n", cyc);
	deb();
	if(all >= cyc * n) {
		ll T = all / (cyc * n);
		for(int k = 0; k < n; k++) {
			i = i - cyc;
			while(i < 0) i = n + i;
			distr(cyc * ll(d), i, T);
		}
		all = all % (cyc * n);
	}
	deb();
	md = 0;
	while(all >= cyc) {
		i = i - cyc;
		while(i < 0) i = n + i;
		distr(cyc * ll(d), i);
		all -= cyc;
	}
	deb();
	end();
}
