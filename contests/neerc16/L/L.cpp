#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }
#ifdef ONLINE_JUDGE
#	define debug(args...) {}
#else
#	define debug(args...) fprintf(stderr, args)
#endif

const ll MX = 1e18 + 7;
const int N = 3e3;

ll a, b;
ll memo[N][N][2];
ll pri[N];
bool sieve[N];
ll m;
ll ign, go;
ll st[N], ss;
ll car[N];
bool prrr;
char str[N];

ll pd (int p, int s, int k = 0) {
	if (s == 0) return !k;
	assert(p < m);
	if (s < 0 || pri[p] > s) return 0;

	ll & me = memo[p][s][0];
	ll & qt = memo[p][s][1];

	if (me != -1) {
		if (k)
			return me;
		else
			return qt;
	}
	
	qt = min(MX, pd(p+1, s) + pd(p+1, s-pri[p]));
	if (pd(p+1, s-pri[p]) == MX) {
		me = MX;
	} else {
		if (log10(car[p] + 2) + log10(pd(p+1, s-pri[p])) > 18. + log10(2))
			me = MX;
		else
			me = min(MX, ll(car[p]+2)*pd(p+1, s-pri[p]) + pd(p+1, s-pri[p], 1) + pd(p+1, s, 1));
	}

	if (k)
		return me;
	else
		return qt;
}

void printa (char c) {
	if (ign) {
		ign--;
	} else if (go) {
		putchar(c);
		go--;
	}
}

void printa (ll x) {
	if (!go) return;
	int i = 0;
	while (x) {
		str[i] = (x%10) + '0';
		x /= 10;
		i++;
	}

	while (i--)
		printa(str[i]);
}

void printa () {
	bool ok = 0;
	printa('[');
	for (ll i = 0; i < ss; i++) {
		if (ok) {
			printa(',');
			printa(' ');
		}
		printa(st[i]);
		ok = 1;
	}
	printa(']');
	printa(',');
	printa(' ');
}

void build (int p, int s, ll x) {
	if (go == 0) {
		return;
	}

	ll qtd = pd(p,s)*x + pd(p, s, 1); // tem q checar se estoura
	if (log10(pd(p,s)) + log10(x) >= 18. + log10(2))
		qtd = MX;
	//printf("%d %d %lld -> %lld\n", p, s, x, qtd);
	if (ign >= qtd) {
		ign -= qtd;
	} else if (s == 0) {
		printa();
	} else {
		st[ss++] = pri[p];
		build(p+1, s-pri[p], x+car[p]+2);
		ss--;
		build(p+1, s, x);
	}
}

int main() {
	freopen("list.in", "r", stdin);
	freopen("list.out", "w", stdout);
	memset(memo, -1, sizeof memo);
	scanf("%lld %lld", &a, &b);
	
	for (ll i = 2; i < N; i++) {
		if (sieve[i]) continue;
		for (ll j = i*i; j < N; j += i)
			sieve[j] = 1;
	}

	for (ll i = 2; i < N; i++) {
		if (!sieve[i]) {
			ll x =i;
			while (x) {
				car[m]++;
				x/=10;
			}
			pri[m++] = i;
		}
	}

	//printf("%lld %lld\n", pd(a, b, 0), pd(a, b, 1));
	//return 0;

	ign = a-1;
	go = b - a + 1;

	for (ll i = 2; i < N && (ign || go); i++)
		build(0, i, 2);
	putchar('\n');
}
