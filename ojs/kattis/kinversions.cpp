#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef unsigned long long ull;
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }

typedef complex<double> num;
const double pi = acos(-1.0);
const int N = (1 << 21);
int p[N];

// DFT se type = 1 e IDFT se i = -1
// Se for multiplicar lembre-se de deixar cada vetor com n>=soma dos graus dos pols
// n tem que ser potencia de 2
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

num pa[N], pb[N], da[N], db[N];

char s[N];
int main() {
	scanf("%s", s);
	int n = strlen(s), i;
	for(i = 0; s[i]; i++) {
		if(s[i] == 'A') pa[i] = 1;
		else pb[n-1-i] = 1;
	}
	FFT(pa, da, N, 1);
	FFT(pb, db, N, 1);
	for(i = 0; i < N; i++) da[i] *= db[i];
	FFT(da, db, N, -1);
	for(i = n; i <= n - 1 + n - 1; i++)
		printf("%.0f\n", abs(db[i]));
}
