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

typedef complex<double> num;
const double pi = acos(-1.0);
const int N = 612345;
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

num pol[N], aux[N];
num aux2[N];

inline void sqr(num pol[], int n) {
	FFT(pol, aux, n, 1);
	for(int i = 0; i < n; i++) aux[i] = aux[i] * aux[i];
	FFT(aux, pol, n, -1);
}


template<class num> inline void rd(num &x) {
	char c;
	while(isspace(c = getchar()));
	bool neg = false;
	if(!isdigit(c)) neg = (c == '-'), x = 0;
	else x = c - '0';
	while(isdigit(c = getchar()))
		x = (x << 3) + (x << 1) + c - '0';
	if(neg) x = -x;
}

int main() {
	int i, n, k, q, x, j;
	rd(n); rd(k); rd(q);
	for(i = 0; i < k; i++) {
		rd(x);
		pol[x] = 1;
	}
	pol[0] = 1;
	for(i = 1; i <= n; i++)
		if(pol[i] != num(0))
			for(j = i + i; j <= 200000; j += i)
				pol[j] = 1;
	for(i = 0; i < 9; i++) {
		for(j = 0; j <= 200000; j++) aux2[j] = pol[j];
		sqr(pol, (1 << 19));
		for(j = 0; j <= 200000; j++)
			pol[j] = (abs(pol[j]) > .5? 1 : 0);
		for(j = 200001; j < (1 << 19); j++) pol[j] = 0;
		for(j = 0; j <= 200000; j++)
			if(pol[j] != aux2[j])
				break;
		if(j == 200001) break;
	}
	for(i = 0; i < q; i++) {
		rd(x);
		if(abs(pol[x]) > .5) puts("Yes");
		else puts("No");
	}

}
