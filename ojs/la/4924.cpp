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

int a[1002], p[1002];
int main() {
	int i, j, n, k, s;
	for_tests(t, tt) {
		scanf("%d %d", &n, &k);
		for(i = 0; i < k; i++)
			scanf("%d", &p[i]);
		sort(p, p + k);
		int less = (lower_bound(p, p + k, 32) - p);
		int mx = 0;
		for(i = 0; i < (1 << less); i++) {
			memset(a, 0, sizeof a);
			for(j = 0; j < less; j++)
				if(i & (1 << j))
					for(s = p[j]; s <= n; s += p[j])
						a[s] = !a[s];
			for(j = less; j < k; j++) {
				int ct = 0;
				for(s = p[j]; s <= n; s += p[j])
					ct += 2 * (!a[s]) - 1;
				if(ct > 0)
					for(int s = p[j]; s <= n; s += p[j])
						a[s] = !a[s];
			}
			mx = max(mx, accumulate(a, a + n + 1, 0));
		}
		printf("Case #%d: %d\n", tt, mx);
	}
}
