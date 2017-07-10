#include <bits/stdc++.h>
using namespace std;
#define pb push_back
typedef long long ll;
typedef pair<int, int> pii;
ll M;

typedef complex<long double> num;
const double pi = acos(-1.);
const int N = 612345;
int p[N];
const int p2 = 1 << 19;

void FFT(num v[], num ans[], int n, int type) {
	assert(!(n & (n - 1)));
	int i, sz, o;
	p[0] = 0;
	for(i = 1; i < n; i++) p[i] = (p[i >> 1] >> 1) | ((i & 1)? (n >> 1) : 0);
	for(i = 0; i < n; i++) ans[i] = v[p[i]];
	for(sz = 1; sz < n; sz <<= 1) {
		const num wn(cos(type * pi / sz), sin(type * pi / sz));
		for(o = 0; o < n; o += (sz << 1)) {
			num w = 1;
			for(i = 0; i < sz; i++) {
				const num u = ans[o + i], t = w * ans[o + sz + i];
				ans[o + i] = u + t;
				ans[o + i + sz] = u - t;
				w *= wn;
			}
		}
	}
	if(type == -1) for(i = 0; i < n; i++) ans[i] /= n;
}

inline ll mod(ll x) { return x % M; }

inline ll fexp(ll x, ll p) {
	ll r = 1;
	for(; p; p >>= 1, x = mod(x * x))
		if(p & 1)
			r = mod(r * x);
	return r;
}

num a[N], b[N], c[N];
ll ct[N];

int main() {
	int n, i;
	scanf("%lld %lld", &n, &M);
	for(i = 1; i < M; i++) {
		ll x = fexp(i, n);
		ct[x]++;
	}
	for(i = 0; i < M; i++) a[i] = ct[i];
	FFT(a, b, p2, 1);
	for(i = 0; i < p2; i++) b[i] = b[i] * b[i];
	FFT(b, a, p2, -1);
	ll tot = 0;
	for(i = 0; i < 2 * M; i++) {
		ll fi = ll(real(a[i]) + .5);
		//printf("+= %lld * %lld\n", fi, ct[i]);
		tot += fi * ct[i % M];
	}
	printf("%lld\n", tot);
}
