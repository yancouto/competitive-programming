// WRONG
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
const int N = 212345;
ll a[N], suf[N], suf2[N];
vector<int> add[N], rem[N];

int main() {
	int i, n;
	scanf("%d", &n);
	for(i = 0; i < n; i++)
		scanf("%lld", &a[i]);
	a[n++] = 0;
	for(i = n - 1; i >= 0; i--)
		suf[i] = suf[i + 1] + a[i];
	for(i = n - 1; i >= 0; i--)
		suf2[i] = suf2[i + 1] + suf[i];
	for(i = 0; i < n; i++)
		printf("%lld ", a[i]);
	printf("\n-------------\n");
	for(i = 0; i < n; i++)
		printf("%lld ", suf[i]);
	printf("\n-------------\n");
	for(i = 0; i < n; i++)
		printf("%lld ", suf2[i]);
	printf("\n-------------\n");
	ll cur = 0;	
	for(i = n - 1; i >= 0; i--) {
		cur = suf2[i];
		if(a[i] > 0) continue;
		if(suf[i] < 0) {
			ll k = 1ll + ((cur - suf[i] - 1) / (-suf[i]));
			printf("suf[%d] < 0: k = %lld\n", i, k);
			k = max(k, 1ll);
			printf("%d .. %lld\n", 0, i - k + 1);
			add[0].pb(i);
			rem[i - k + 1].pb(i);
			//add[i - k + 1].pb(i);
		} else if(suf[i] > 0 && cur < 0) {
			ll k = 1ll + ((-cur) / suf[i]);
			printf("suf[%d] > 0: k = %lld\n", i, k);
			add[i - k + 1].pb(i);
		} else if(suf[i] == 0 && cur <= 0) {
			printf("suf empty %d\n", i);
			add[0].pb(i);
		}
	}
	set<int> ig;
	ll mx = 0;
	for(i = 0; i < n; i++) {
		cur = suf2[i];
		for(int x : add[i]) ig.insert(x);
		printf("at %d:", i);
		for(int x : ig) printf(" %d", x);
		printf("\n");
		int j = *ig.begin();
		mx = max(mx, cur - suf2[j] - ll(j - i) * suf[j]);
		for(int x : rem[i]) ig.erase(x);
		ig.erase(i);
	}
	printf("%lld\n", mx);
}
