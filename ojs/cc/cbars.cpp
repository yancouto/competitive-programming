#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef pair<int, int> pii;
typedef unsigned long long ull;
typedef long long ll;
typedef long double ld;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
template<typename T> inline T abs(T t) { return t < 0? -t : t; }
const ull modn = 1000000007;
inline ull mod(ull x) { return x % modn; }

ull adj[64][64];
int m; ull b;
bool ok(int x, int y) {
	for(int i = 0; i < m - 1; i++)
		if((x & (3 << i)) == (3 << i) && (y & (3 << i)) == (3 << i))
			return false;
	for(int i = 0; i < m - 1; i++)
		if((x & (3 << i)) == 0 && (y & (3 << i)) == 0)
			return false;
	return true;
}

void mult(ull a[64][64], ull b[64][64], ull c[64][64]) {
	int i, j, k;
	for(i = 0; i < m; i++)
		for(j = 0; j < m; j++) {
			c[i][j] = 0;
			for(k = 0; k < m; k++)
				c[i][j] = mod(c[i][j] + a[i][k] * b[k][j]);
		}
}
void cp(ull a[64][64], ull b[64][64]) {
	int i, j;
	for(i = 0; i < m; i++)
		for(j = 0; j < m; j++)
			b[i][j] = a[i][j];
}
ull a1[64][64], a2[64][64];

void fexp(ull p) {
	cp(adj, a1);
	for(int i = 0; i < m; i++)
		for(int j = 0; j < m; j++)
			adj[i][j] = (i == j);
	for(ull i = 1; i <= p; i <<= 1) {
		if(i & p) {
			mult(adj, a1, a2);
			cp(a2, adj);
		}
		mult(a1, a1, a2);
		cp(a2, a1);
	}
}

int main() {
	int i, j;
	scanf("%d %llu", &m, &b); 
	for(i = 0; i < (1 << m); i++)
		for(j = i; j < (1 << m); j++)
			adj[i][j] = adj[j][i] = ok(i, j);
	m = 1 << m;
	fexp(b - 1);
	ull tot = 0;
	for(i = 0; i < m; i++)
		for(j = 0; j < m; j++)
			tot = mod(tot + adj[i][j]);
	printf("%llu\n", tot);
	return 0;
}
