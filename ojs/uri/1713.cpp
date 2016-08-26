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
const int modn = 10000;
inline int mod(int x) { return x % modn; }
int n, l, s, t;
void mult(int a[102][102], int b[102][102], int c[102][102]) {
	int i, j, k;
	for(i = 0; i < n; i++)
		for(j = 0; j < n; j++) {
			c[i][j] = 0;
			for(k = 0; k < n; k++)
				c[i][j] = mod(c[i][j] + a[i][k] * b[k][j]);
		}
}
void cp(int a[102][102], int b[102][102]) {
	int i, j;
	for(i = 0; i < n; i++)
		for(j = 0; j < n; j++)
			b[i][j] = a[i][j];
}
int adj[102][102], resp[102][102];
int aux[102][102];
void fexp() {
	int i, j;
	for(i = 0; i < n; i++)
		for(j = 0; j < n; j++)
			resp[i][j] = (i == j);
	for(i = 1; i <= l; i <<= 1) {
		if(i & l) {
			mult(adj, resp, aux);
			cp(aux, resp);
		}
		mult(adj, adj, aux);
		cp(aux, adj);
	}
}

int main() {
	int a, b, c, d, i, j;
	while(scanf("%d %d", &n, &l) != EOF) {
		scanf("%d %d", &s, &t);
		for(i = 0; i < n; i++) {
			scanf("%d %d %d %d", &a, &b, &c, &d);
			for(j = 0; j < n; j++) adj[i][j] = 0;
			adj[i][--a]++; adj[i][--b]++; adj[i][--c]++; adj[i][--d]++;
		}
		fexp();
		printf("%d\n", resp[--s][--t]);
	}
	return 0;
}
