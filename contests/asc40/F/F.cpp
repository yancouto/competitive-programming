#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
typedef long long ll;
typedef pair<ll, ll> pii;
#define pb push_back
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }

#define str first
#define sqr second

bool test(int sz, int i, ll str) {
	if((sz - i) & 1) return false;
	int k = (sz - i) / 2;
	int full = (1ll << k) - 1;
	return ((str >> i) & full) == (str >> (i + k));
}

string bin(ll x) { return bitset<4>(x).to_string(); }

int main() {
#ifdef ONLINE_JUDGE
#	define LLD "%I64d"
#	define debug(...) fprintf(stderr, ...)
	freopen("free.in", "r", stdin);
	freopen("free.out", "w", stdout);
#else
#	define LLD "%lld"
#	define debug(...) {}
#endif
	int i, j, n;
	scanf("%d", &n);
	vector<pii> v, v2;
	v.pb(pii(0, 0));
	for(i = 1; i <= n; i++) {
		v2.clear();
		for(pii bm : v) {
			for(ll k = 0; k < 2; k++) {
				pii B(bm.str | (k << (i - 1)), bm.sqr | (1ll << (i - 1)));
				int cur = 0;
				for(j = 0; j < i; j++) {
					if(((B.sqr >> j) & 1) && test(i, j, B.str)) {
						B.sqr ^= (1ll << j);
					}
					cur += ((B.sqr >> j) & 1);
					if(cur * 2 < (j + 1)) break;
				}
				if(j == i) v2.pb(B);
			}
		}
		v.swap(v2);
	}
	printf("%d\n", (int) v.size());
	for(pii B : v) {
		ll x = B.str;
		for(i = 0; i < n; i++)
			putchar(((x >> i) & 1) + '0');
		putchar('\n');
	}
}
