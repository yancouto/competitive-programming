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

ll _bs[2123], a[112345], pd[112345];
ll *bs = _bs + 1050;

inline ll eval(ll j, ll ai) {
	return j * ai + j * j * ai * ai + pd[j];
}

int main() {
	int i, n, j;
	scanf("%d", &n);
	for(i = 0; i < n; i++)
		scanf("%lld", &a[i]);
	for(i = -1000; i <= 1000; i++)
		bs[i] = n - 1;
	for(i = n - 2; i >= 0; i--) {
		j = bs[a[i]];
		pd[i] = eval(j, a[i]) - ll(i) * a[i] - ll(i) * ll(i) * a[i] * a[i];
		if(i == 0) break;
		for(j = -1000; j <= 1000; j++)
			if(eval(i, j) < eval(bs[j], j))
				bs[j] = i;
	}
	printf("%lld\n", pd[0]);
}
