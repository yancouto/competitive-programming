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
const int N = 100009;
int a[N], b[N];

int main() {
	int i, n;
	while(scanf("%d", &n) != EOF && n) {
		ll tot = 0;
		for(i = 0; i < n; i++) {
			scanf("%d", &a[i]);
			tot += a[i];
		}
		if(tot & 1) { puts("No"); continue; }
		tot /= 2;
		for(i = n - 1; i >= 0; i--) {
			if(tot >= a[i]) {
				b[i] = -1;
				tot -= a[i];
			} else b[i] = 1;
		}
		assert(tot == 0);
		puts("Yes");
		for(i = 0; i < n; i++)
			printf("%d ", b[i]);
		putchar('\n');
	}
}
