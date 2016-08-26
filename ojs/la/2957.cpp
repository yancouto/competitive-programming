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
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }
const int N = 1002;
int a[N][N], b[N][N]; ll c[N], d[N];
ll aux[N]; int n;

void mult(int x[N][N], ll y[N]) {
	int i, j;
	for(i = 0; i < n; i++) {
		aux[i] = 0;
		for(j = 0; j < n; j++)
			aux[i] += y[j] * ll(x[i][j]);
	}
	for(i = 0; i < n; i++)
		y[i] = aux[i];
}

int main() {
	int i, j;
	srand(time(NULL));
	while(true) {
		scanf("%d", &n);
		if(!n) return 0;
		for(i = 0; i < n; i++)
			for(j = 0; j < n; j++)
				scanf("%d", &a[i][j]);
		for(i = 0; i < n; i++)
			for(j = 0; j < n; j++)
				scanf("%d", &b[i][j]);
		bool ok = true;
		for(i = 0; ok && i < n; i++) {
			for(j = 0; j < n; j++)
				d[i] = c[i] = rand();
			mult(a, c); mult(a, c);
			mult(b, d);
			for(j = 0; j < n; j++)
				ok &= (c[j] == d[j]);
		}
		if(ok) puts("YES");
		else puts("NO");
	}
}
