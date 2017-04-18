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

int main() {
	int i, n, x;
	for_tests(t, tt) {
		scanf("%d", &n);
		int n1 = 0;
		for(i = 0; i < n * n; i++) {
			scanf("%d", &x);
			n1 += !!x;
		}
		if(n1 <= n) { puts("0"); continue; }
		int cur = n;
		for(i = n - 1; i >= 1; i--) {
			cur += 2 * i;
			if(n1 <= cur) { printf("%d\n", n - i); break; }
		}
	}
}
