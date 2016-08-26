#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef unsigned long long ull;
typedef long long ll;
typedef pair<ll, int> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
template<typename T> inline T abs(T t) { return t < 0? -t : t; }
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }
const int N = 100009;
pii ev[N << 1];
int main() {
	int i, n, k, j; ll x, d;
	for_tests(t, tt) {
		scanf("%d %d", &n, &k);
		for(i = 0; i < n; i++) {
			scanf("%lld %lld", &x, &d);
			ev[2*i] = pii(x * d, 1);
			ev[2*i+1] = pii(x * d + x, -1);
		}
		if(n == k) {
			ll t = 1;
			for(i = 0; i < 100; i++)
				t = mod(t * 10);
			printf("%d\n", (int) mod(t + 1));
			continue;
		}
		sort(ev, ev + 2 * n);
		i = 0; int cur = 0;
		ll last = 0; bool last_pos = false;
		ll all = 0;
		while(i < 2*n) {
			if(last_pos) all += ev[i].fst - last;
			j = i;
			while(j < 2*n && ev[j].fst == ev[i].fst)
				cur += ev[j++].snd;
			last_pos = (cur >= n - k);
			last = ev[i].fst;
			i = j;
		}
		printf("%d\n", (int)mod(all));
	}
}
