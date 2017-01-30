#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }
#ifdef ONLINE_JUDGE
#	define debug(args...) {}
#else
#	define debug(args...) fprintf(stderr, args)
#endif

typedef complex<double> num;
const double pi = acos(-1.0);
const int N = 312345;
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


int n;

num p1[N], p2[N], aux[N];
char s[N], t[N];
int v[5][5][N];

int main() {
	int i, j;
	scanf("%s %s", s, t);
	int n = strlen(s);
	reverse(t, t + n);
	for(int A = 0; A < 5; A++)
		for(int a = 0; a < 5; a++) {
			for(i = 0; i < n; i++)
				p1[i] = (s[i] == ('A' + A)),
				p2[i] = (t[i] == ('a' + a));
			for(i = n; i < (1 << 17); i++)
				p1[i] = p2[i] = 0;
			FFT(p1, aux, (1 << 17), 1);
			FFT(p2, p1, (1 << 17), 1);
			for(i = 0; i < (1 << 17); i++)
				p1[i] *= aux[i];
			FFT(p1, aux, (1 << 17), -1);
			for(i = n - 1; i < 2 * n - 1; i++)
				v[A][a][i - (n - 1)] = int(abs(aux[i]) + .5);
			for(i = n - 2; i >= 0; i--)
				v[A][a][i + 1] += int(abs(aux[i]) + .5);
		}
	for(i = 0; i < 5; i++) p[i] = i;
	int best = INT_MAX;
	do {
		for(i = 0; i < n; i++) {
			int cur = 0;
			for(j = 0; j < 5; j++)
				cur += v[j][p[j]][i];
			best = min(best, n - cur);
		}
	} while(next_permutation(p, p + 5));
	printf("%d\n", best);
}
