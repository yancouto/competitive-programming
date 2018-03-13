#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<ll, ll> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }


const int N = 112345;
ll a[N], b[N];

int main() {
	int n, m, i;
	scanf("%d %d", &n, &m);
	for(i = 0; i < n; i++)
		scanf("%lld", &a[i]);
	for(i = 0; i < m; i++)
		scanf("%lld", &b[i]);
	pii mx = pii(0, 0);
	ll acc = accumulate(a, a + n, 0ll);
	ll mx1 = *max_element(a, a + n);
	ll acc2 = accumulate(b, b + m, 0ll);
	ll mx2 = *max_element(b, b + m);
	ll fst = 0, lst = n - 1;
	while(a[fst] != mx1) fst++;
	while(a[lst] != mx1) lst--;
	mx = pii(acc + ll(m - 1) * mx1, acc2 + fst * b[0] + ll(n - lst - 1) * b[m - 1] + ll(lst - fst) * mx2);
	//for(i = 0; i < n; i++) {
	//	mx = max(mx, pii(acc + ll(m - 1) * a[i], acc2 + ll(i) * b[0] + ll(n - i - 1) * b[m - 1]));
	//	printf("%lld, %lld\n", mx.fst, mx.snd);
	//}
	printf("%lld\n", mx.fst * 1000000000ll + mx.snd);
}
