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

const int N = 100;
int n;

void mult(ll A[N][N], ll B[N][N], ll C[N][N]) {
	for(int i = 0; i < n; i++)
		for(int j = 0; j < n; j++) {
			C[i][j] = 0;
			for(int k = 0; k < n; k++)
				C[i][j] = mod(C[i][j] + A[i][k] * B[k][j]);
		}
}

void cp(ll from[N][N], ll to[N][N]) {
	for(int i = 0; i < n; i++)
		for(int j = 0; j < n; j++)
			to[i][j] = from[i][j];
}

ll C[N][N];

void fexp(ll A[N][N], int p, ll B[N][N]) {
	for(int i = 0; i < n; i++)
		for(int j = 0; j < n; j++)
			B[i][j] = (i == j);
	for(; p; p >>= 1) {
		if(p & 1) {
			mult(A, B, C);
			cp(C, B);
		}
		mult(A, A, C);
		cp(C, A);
	}
}

ll A[N][N], B[N][N], bk[N][N];
ll s[N], a[N];

void deb(ll A[N][N]) {
	for(int i = 0; i < n; i++)
		for(int j = 0; j < n; j++)
			printf("%lld%c", A[i][j], " \n"[j == n - 1]);
	puts("=======");
}

int main() {
	for_tests(tn, tt) {
		int i, j, r, k; ll p;
		scanf("%lld %d %d", &p, &r, &k);
		for(i = 0; i < r; i++) scanf("%lld", &s[i]);
		for(i = 0; i < r; i++) scanf("%lld", &a[i]);
		n = (r * k) / __gcd(r, k);
		ll op = p;
		p = (p + (n / k) - 1) / (n / k);
		//p = 1;
		//printf("p %d\n", p);
		for(i = r; i < n; i++) {
			s[i] = 0;
			for(j = 1; j <= r; j++)
				s[i] = mod(s[i] + s[i - j] * a[j - 1]);
		}
		//for(i = 0; i < n ;i++) printf("s[%d] = %lld\n", i, s[i]);
		for(i = 0; i < n; i++) {
			for(j = 0; j <= n; j++) A[i][j] = 0;
			for(j = 1; j <= r; j++) {
				if(i - j < 0) {
					A[i][i - j + n] = mod(A[i][i - j + n] + a[j - 1]);
				} else {
					for(int g = 0; g < n; g++)
						A[i][g] = mod(A[i][g] + A[i - j][g] * a[j - 1]);
				}
			}
		}
		for(j = 0; j < n; j++)
			A[n][j] = (((j + 1) % k) == 0);
		A[n][n] = 1;
		n++;
		//deb(A);
		cp(A, bk);
		fexp(A, p, B);
		//deb(B);
		ll ans = 0;
		for(j = 0; j < n - 1; j++)
			ans = mod(ans + s[j] * B[n - 1][j]);
		fexp(bk, p - 1, B);
		ll ct = (op % ((n - 1) / k));
		if(ct == 0) ct = (n - 1) / k;
		for(ll i = 0; i < n - 1; i++) {
			ll a = 0;
			for(j = 0; j < n - 1; j++)
				a = mod(a + B[i][j] * s[j]);
			//printf("s[%d] = %lld\n", i + (p - 1) * (n - 1) + 1, a);
			if(((i + 1) % k) == 0) {
				if(ct) ct--;
				else ans = mod(ans - a + modn);
			}
		}
		printf("%lld\n", ans);
	}
}
