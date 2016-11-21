#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<ll, int> pii;
#define pb push_back
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }
#ifdef ONLINE_JUDGE
#	define debug(args...) {}
#else
#	define debug(args...) fprintf(stderr, args)
#endif

int n;
const int N = 112345;
pii d[N], p[N];

int main() {
#ifdef ONLINE_JUDGE
	freopen("buffcraft.in", "r", stdin);
	freopen("buffcraft.out", "w", stdout);
#endif
	int i, j, k, n, m;
	ll H;
	scanf("%lld %d %d %d", &H, &k, &n, &m);
	ll best = -1; int bi, bj;
	for(i = 0; i < n; i++) scanf("%lld", &d[i].fst), d[i].snd = i;
	for(i = 0; i < m; i++) scanf("%lld", &p[i].fst), p[i].snd = i;
	sort(d, d + n, greater<pii>());
	sort(p, p + m, greater<pii>());
	for(i = 1; i < n; i++) d[i].fst += d[i - 1].fst;
	for(i = 1; i < m; i++) p[i].fst += p[i - 1].fst;
	for(i = 0; i <= k && i <= n; i++) {
		int j = min(k - i, m);
		ll D = H + (i? d[i - 1].fst : 0ll);
		ll P = 100ll + (j? p[j - 1].fst : 0ll);
		assert(log(D) + log(P) <= log(8e18));
		if(D * P > best) best = D * P, bi = i, bj = j;
	}
	printf("%d %d\n", bi, bj);
	for(i = 0; i < bi; i++) printf("%d ", d[i].snd + 1); putchar('\n');
	for(i = 0; i < bj; i++) printf("%d ", p[i].snd + 1); putchar('\n');
}
