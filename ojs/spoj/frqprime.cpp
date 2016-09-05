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
const int N = 112345;
int dv[N];

int main() {
	int i, j, n, k;
	for(i = 2; i < N; i++)
		if(!dv[i])
			for(j = i+i; j < N; j += i)
				dv[j] = 1;
	for_tests(t, tt) {
		scanf("%d %d", &n, &k);
		int r = 1, ct = 0;
		ll tot = 0;
		for(i = 2; i <= n; i++) {
			while(r < n && ct < k)
				ct += !dv[++r];
			if(r < i) r = i, ct = !dv[i];
			if(ct >= k) tot += n - r + 1;
			ct -= !dv[i];
		}
		printf("%lld\n", tot);
	}
}
