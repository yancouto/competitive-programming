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
const int N = 112345, S = 1123456;

int v[S], seen[S];
ll a[N], b[N], c[N];
int main() {
	int i, n;
	ll M;
	scanf("%d %lld", &n, &M);
	ll B = 0, tot = n;
	for(i = 0; i < n; i++) {
		scanf("%lld %lld %lld", &a[i], &b[i], &c[i]);
		a[i] = max(0ll, a[i] - B);
		ll aux = b[i];
		b[i] = B;
		B += aux;
	}
	for(i = 0; i < S; i++) v[i] = INT_MAX;
	for(i = n - 1; i >= 0; i--) v[a[i]] = i;
	for(i = S-2; i >= 0; i--) v[i] = min(v[i], v[i + 1]);
	int ct = 0;
	while(M < S && !seen[M]) {
		seen[M] = true;
		if(v[M] == INT_MAX) { printf("%lld\n", tot); return 0; }
		i = v[M];
		tot += i + 1;
		M += b[i] - c[i];
		if(M <= 0) { puts("-1"); return 0; }
	}
	if(M >= S) printf("%lld\n", tot);
	else puts("-1");
}
