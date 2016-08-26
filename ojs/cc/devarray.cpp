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
	int i, n, q, x;
	scanf("%d %d", &n, &q);
	for(i = 0; i < n; i++) scanf("%d", &a[i]);
	int mn = *min_element(a, a + n), mx = *max_element(a, a + n);
	for(i = 0; i < q; i++) {
		scanf("%d", &x);
		if(x >= mn && x <= mx) puts("Yes");
		else puts("No");
	}
}
