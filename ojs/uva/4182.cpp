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
const int N = 500009;
int f[N], dv[N], ct[N], p[N];

int main() {
	int i, j, n, x; ll m;
	for(i = 2; i < N; i++)
		if(!dv[i])
			for(j = i; j < N; j += i)
				dv[j] = i;
	for_tests(t, tt) {
		scanf("%d %lld", &n, &m);
		for(i = 1; i < n; i++) {
			scanf("%d", &p[i]); p[i]--;
			f[i] = 1;
		}
		f[0] = 1;
		for(i = n - 1; i > 0; i--)
			f[p[i]] += f[i];
		for(i = 0; i < n; i++)
			ct[i] = 0;
		for(i = 2; i < n; i++) {
			int x = i;
			while(x != 1) {
				ct[dv[x]]++;
				x /= dv[x];
			}
		}
		for(i = 1; i < n; i++) {
			int x = f[i];
			while(x != 1) {
				ct[dv[x]]--;
				x /= dv[x];
			}
		}
		ll v = 1;
		for(i = 2; i < n; i++)
			while(ct[i]--)
				v = (v * ll(i)) % m;
		printf("%lld\n", v);
	}
}
