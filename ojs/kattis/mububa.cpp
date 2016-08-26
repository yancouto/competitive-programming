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
const int N = 3009;
ll acc[N]; int memo[N][N], mn[N][N], a[N];
int main() {
	int i, n, x;
	scanf("%d", &n);
	ll last = 0, cur = 0; int ex = 0;
	for(i = 0; i < n; i++) {
		scanf("%d", &a[i]);
		acc[i] = a[i] + (i? acc[i - 1] : 0);
	}
	acc[n] = LLONG_MAX;
	for(i = n - 1; i >= 0; i--)
		for(last = i; last >= 0; last--) {
			int &ret = memo[i][last];
			ll val = i? acc[i - 1] : 0;
			if(last) val -= acc[last - 1];
			int l = i, r = n;
			ll v = 0;
			if(i) v = acc[i - 1];
			while(l < r) {
				int m = (l + r) / 2;
				if(acc[m] - v >= val) r = m;
				else l = m + 1;
			}
			if(l == n) ret = 0;
			else ret = 1 + mn[l + 1][i];
			mn[i][last] = max(ret, mn[i + 1][last]);
		}
	printf("%d\n", memo[0][0]);
}
