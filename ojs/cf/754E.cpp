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
const int N = 1100;
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


int n, m;
char g[N][N];
int r, c;
char pa[N][N];

num a[N], b[N], aux[N];

int A[412][412][412];
int q[N];

int main() {
	int i, j, k;
	scanf("%d %d", &n, &m);
	for(i = 0; i < n; i++) scanf("%s", g[i]);
	scanf("%d %d", &r, &c);
	for(i = 0; i < r; i++) scanf("%s", pa[i]);

	for(k = 0; k < 26; k++)
		for(i = 0; i < n; i++)
			for(j = 0; j < r; j++) {
				for(int ii = 0; ii < m; ii++)
					a[ii] = (g[i][ii] == ('a' + k));
				for(int ii = m; ii < 1024; ii++) a[ii] = 0;
				for(int jj = 0; jj < c; jj++)
					b[jj] = (pa[j][c - 1 - jj] == ('a' + k));
				for(int jj = c; jj < 1024; jj++) b[jj] = 0;
				
				//for(int ii = 0; ii < m; ii++)
				//	printf("%d%c", int(abs(a[ii]) + .5), " \n"[ii == m - 1]);
				//for(int ii = 0; ii < c; ii++)
				//	printf("%d%c", int(abs(b[ii]) + .5), " \n"[ii == c - 1]);


				FFT(a, aux, 1024, 1);
				FFT(b, a, 1024, 1);
				for(int ii = 0; ii < 1024; ii++)
					a[ii] *= aux[ii];
				FFT(a, b, 1024, -1);
				//for(int ii = 0; ii < m + c; ii++)
				//	printf("%d%c", int(abs(b[ii]) + .5), " \n"[ii == m + c - 1]);
				for(int ii = c - 1; ii < c - 1 + m; ii++)
					A[i][j][ii - (c - 1)] += int(abs(b[ii]) + .5);
				for(int ii = 0; ii < c - 1; ii++)
					A[i][j][(550*m - (c - 1 - ii) ) % m] += int(abs(b[ii]) + .5);
			}
	for(i = 0; i < r; i++)
		for(j = 0; j < c; j++)
			q[i] += (pa[i][j] == '?');
	
	//for(i = 0; i < n; i++)
	//	for(j = 0; j < r; j++) {
	//		printf("Row (%d) and (%d)\n", i, j);
	//		for(k = 0; k < m; k++)
	//			printf("%d%c", A[i][j][k], " \n"[k == m - 1]);
	//	}
	for(i = 0; i < n; i++)
		for(j = 0; j < m; j++) {
			for(k = 0; k < r; k++)
				if(A[(i + k) % n][k][j] + q[k] != c)
					break;
			printf("%d", (k == r));
			if(j == m - 1) putchar('\n');
		}
}
