#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef unsigned long long ull;
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }
const int N = 212345;

int sn = 0;
ll sz[N], a[N];

int main() {
#ifdef ONLINE_JUDGE
#	define LLD "%I64d"
#	define debug(args...) {}
	freopen("approximation.in", "r", stdin);
	freopen("approximation.out", "w", stdout);
#else
#	define LLD "%lld"
#	define debug(args...) fprintf(stderr, args)
#endif
	int i, j, n;
	scanf("%d", &n);
	for(i = 0; i < n; i++) {
		sz[sn] = 1;
		scanf(LLD, &a[sn++]);
		while(sn > 1 && a[sn - 1] * sz[sn - 2] < a[sn - 2] * sz[sn - 1]) {
			a[sn - 2] += a[sn - 1];
			sz[sn - 2] += sz[sn - 1];
			sn--;
		}
	}
	for(i = 0; i < sn; i++) {
		double v = double(a[i]) / sz[i];
		for(j = 0; j < sz[i]; j++)
			printf("%.14f ", v);
	}
	putchar('\n');
}
