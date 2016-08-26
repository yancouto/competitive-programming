// UNFINISHED
#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef unsigned long long ull;
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
template<typename T> inline T abs(T t) { return t < 0? -t : t; }
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }
const int N = 312345;
int s[N]; char d[N];
int p[N], ans[N];

int main() {
	int i, j, n, m; ll t;
	scanf("%d %d %lld", &n, &m, &t);
	bool all_eq = true;
	for(i = 0; i < n; i++) {
		scanf("%d %c", &s[i], &d[i]);
		p[i] = i;
		if(i > 0) all_eq &= d[i] == d[i - 1];
	}
	sort(p, p + n, [](int i, int j) { return s[i] < s[j]; });
	char d0 = d[p[0]];
	int s0 = s[p[0]];
	ll tot = 0;
	for(j = 1; j < n; j++) {
		i = p[j];
		if(d0 == d[i]) continue;
		ll dis = ll(d0 == 'R'? s[i] - s0 : s0 + m - s[i]);
		if(dis > t * 2ll) continue;		
		printf("[%d] first col at %lld/2 + %lld / 2 * k\n", s[i], dis, m);
		tot += 1ll + (2ll * t - dis) / ll(m);
	}
	printf("%lld coll\n", tot);
	int st;
	if(d0 == 'R') st = tot % n;
	else st = (n - (tot % n)) % n;
	for(j = 0; j < n; j++) {
		int k = p[j];
		i = p[(j + st) % n];
		if(d[k] == 'L') ans[i] = int((ll(s[k]) - (t % m) + ll(m) - 1ll) % m) + 1;
		else ans[i] = int((ll(s[k]) + (t % m) - 1) % m) + 1;
		printf("ans of %d[%d] that was [%d] = %d\n", i, s[i], s[k], ans[i]);
	}
	for(i = 0; i < n; i++)
		printf("%d ", ans[i]);
	putchar('\n');
}
