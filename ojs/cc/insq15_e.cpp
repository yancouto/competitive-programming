#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef unsigned long long ull;
typedef long long ll;
typedef long double ld;
typedef pair<ll, int> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
template<typename T> inline T abs(T t) { return t < 0? -t : t; }
const ull modn = 1000000007;
inline ull mod(ull x) { return x % modn; }

pii ps[10009];
int main() {
	int n, s, m, q, k, i;
	scanf("%d", &n);
	for(i = 0; i < n; i++) {
		scanf("%d %d", &s, &m);
		ps[i].fst = -ll(s) * ll(m);
		ps[i].snd = i;
	}
	sort(ps, ps + n);
	scanf("%d", &q);
	for(i = 0; i < q; i++) {
		scanf("%d", &k);
		printf("%d\n", ps[k - 1].snd + 1);
	}
}
