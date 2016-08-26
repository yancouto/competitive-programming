#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef pair<int, int> pii;
typedef unsigned long long ull;
typedef long long ll;
typedef long double ld;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
template<typename T> inline T abs(T t) { return t < 0? -t : t; }
const ull modn = 1000000007;
inline ull mod(ull x) { return x % modn; }

ll mdc(ll a, ll b) {
	if(b == 0) return a;
	return mdc(b, a % b);
}

ll a[102], used[100009];
int main() {
	int i, j, n; ll t; ll tc = 0;
	while(true) {
		scanf("%d %lld", &n, &t);
		if(!n) return 0;
		tc++;
		bool ok = true;
		int m = 0;
		for(i = 0; i < n; i++) {
			scanf("%lld", &a[i]);
			used[a[i]] = tc;
			if(t % a[i]) ok = false;
		}
		if(!ok) { puts("impossivel"); continue; }
		ll mm = a[0];
		for(i = 1; i < n; i++)
			mm = (mm / mdc(mm, a[i])) * a[i];
		ll x;
		for(x = 2; x <= t; x++)
			if(((mm / mdc(mm, x)) * x) == t && used[x] != tc)
				break;
		if(x <= t) printf("%lld\n", x);
		else puts("impossivel");
	}
}
