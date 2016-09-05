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

int a[112345];
int main() {
	int i, n, q, l, r, v;
	for_tests(t, tt) {
		scanf("%d %d", &n, &q);
		for(i = 0; i < n; i++) a[i] = 0;
		for(i = 0; i < q; i++) {
			scanf("%d %d %d", &l, &r, &v);
			a[l] += v; a[r + 1] -= v;
		}
		for(i = 1; i < n; i++) a[i] += a[i - 1];
		for_tests(q, qq) {
			scanf("%d", &l);
			printf("%d\n", a[l]);
		}
	}
}
