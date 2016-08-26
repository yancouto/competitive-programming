#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef unsigned long long ull;
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
template<typename T> inline T abs(T t) { return t < 0? -t : t; }
const ll modn = 998244353;
inline ll mod(ll x) { return x % modn; }
const int N = 5;

int o[256];
ll M[N][N], aux[N][N], res[N][N];
ll pot[N][N];

void cp(ll src[N][N], ll dst[N][N]) {
	int i, j;
	for(i = 0; i < N; i++)
		for(j = 0; j < N; j++)
			dst[i][j] = src[i][j];
}

void mult(ll A[N][N], ll B[N][N], ll C[N][N]) {
	int i, j, k;
	for(i = 0; i < N; i++)
		for(j = 0; j < N; j++) {
			C[i][j] = 0;
			for(k = 0; k < N; k++)
				C[i][j] += mod(A[i][k] * B[k][j]);
			C[i][j] = mod(C[i][j]);
		}
}

void exp(int n) {
	int i, j;
	for(i = 0; i < 5; i++)
		for(j = 0; j < 5; j++)
			res[i][j] = (i == j);
	cp(M, pot);
	for(; n; n >>= 1) {
		if(n & 1) mult(pot, res, aux), cp(aux, res);
		mult(pot, pot, aux); cp(aux, pot);
	}
}

string ed[20] = {
	"GR", "GG", "GE", "GF",
	"RR", "RR", "RG", "RE", "RE",
	"EE", "ET",
	"TT", "TR", "TE", "TE"
};

void add(string s) {
	M[o[s[0]]][o[s[1]]]++;
}

int main() {
	freopen("figure.in", "r", stdin);
	freopen("figure.out", "w", stdout);
	int i = 0, n;
	for(char c : "GRETF")
		o[c] = i++;
	for(int i = 0; i < 15; i++)
		add(ed[i]);
	while(scanf("%d", &n) != EOF && n) {
		n++;
		exp(n);
		printf("%d\n", (int) res[o['G']][o['F']]);
	}
}
