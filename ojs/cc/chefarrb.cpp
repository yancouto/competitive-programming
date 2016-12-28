#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }

const int L = 30, N = 112345;

set<int> on[L];
int a[N];

int main() {
	for_tests(t, tt) {
		int i, j, n, k;
		scanf("%d %d", &n, &k);
		for(j = 0; j < L; j++) on[j].clear();
		for(i = 0; i < n; i++) {
			scanf("%d", &a[i]);
			for(j = 0; j < L; j++)
				if(a[i] & (1 << j))
					on[j].insert(i);
		}
		ll tot = 0;
		for(i = 0; i < n; i++) {
			int x = a[i], g = i;
			if(x >= k) { tot += n - i; continue; }
			while(true) {
				int nx = INT_MAX;
				for(j = 0; j < L; j++)
					if(!(x & (1 << j)) && on[j].upper_bound(g) != on[j].end())
						nx = min(nx, *on[j].upper_bound(g));
				if(nx == INT_MAX) break;
				g = nx;
				x |= a[g];
				if(x >= k) { tot += (n - g); break; }
			}
		}
		printf("%lld\n", tot);
	}
}
