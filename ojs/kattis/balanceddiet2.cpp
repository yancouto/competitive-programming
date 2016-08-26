#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef unsigned long long ull;
typedef long long ll;
typedef pair<ll, ll> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
template<typename T> inline T abs(T t) { return t < 0? -t : t; }
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }
const int N = 1523456;

int a[N], lst[N];
vector<int> ev[N];
ll s[N], val[N];

int main() {
	int i, m, k, x;
	scanf("%d %d", &m, &k);
	for(i = 0; i < m; i++)
		scanf("%d", &a[i]);
	ll K = accumulate(a, a + m, 0ll);
	for(i = 0; i < k; i++) {
		scanf("%d", &x);
		s[x - 1]++;
	}
	for(i = 0; i < m; i++) {
		val[i] = (s[i] + 1ll) * K - ll(k) * a[i];
		lst[i] = 0;
		ev[(val[i] + a[i] - 1) / a[i]].pb(i);
	}
	int e = 0;
	for(i = 1; i <= 2*K; i++) {
		e += ev[i].size();
		if(e > i) { printf("%d\n", i-1); return 0; }
		for(int j : ev[i]) {
			val[j] -= ll(i - lst[j]) * a[j];
			lst[j] = i;
			assert(val[j] <= 0 && val[j] + a[j] > 0);
			val[j] += K;
			ev[i + (val[j] + a[j] - 1) / a[j]].pb(j);
		}
	}
	puts("forever");
}
