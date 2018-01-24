#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
const ll modn = 10000;
inline ll mod(ll x) { return x % modn; }

const int N = 109;
ll A[N][N];
int n;

void mult(ll A[N][N], ll B[N][N], ll C[N][N]) {
	for(int i = 0; i < n; i++)
		for(int j = 0; j < n; j++) {
			C[i][j] = 0;
			for(int k = 0; k < n; k++)
				C[i][j] = mod(C[i][j] + A[i][k] * B[k][j]);
		}
}

void cp(ll A[N][N], ll B[N][N]) {
	for(int i = 0; i < n; i++)
		for(int j = 0; j < n; j++)
			B[i][j] = A[i][j];
}

ll R[N][N], aux[N][N];

void exp(ll M[N][N], ll k) {
	for(int i = 0; i < n; i++)
		for(int j = 0; j < n; j++)
			R[i][j] = (i == j);
	for(; k; k >>= 1) {
		if(k & 1) {
			mult(M, R, aux);
			cp(aux, R);
		}
		mult(M, M, aux);
		cp(aux, M);
	}
}

ll M[N][N];
int main() {
	ll L;
	int s, t, i, j;
	scanf("%d %lld", &n, &L);
	scanf("%d %d", &s, &t);
	for(i = 0; i < n; i++) {
		for(j = 0; j < 4; j++) {
			int x;
			scanf("%d", &x);
			M[i][x - 1]++;
		}
	}
	exp(M, L);
	printf("%lld\n", R[s-1][t-1]);
}
