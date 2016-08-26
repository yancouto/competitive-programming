#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef unsigned long long ull;
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }
#ifdef ONLINE_JUDGE
#	define lld I64d
#	define debug(args...) {}
#else
#	define debug(args...) fprintf(stderr, args)
#endif
const int n = 5000, k = 2000, x = 100, N = 5123;
mt19937 gen(345234);
uniform_real_distribution <double> prob(0, 1);
inline double P() { return prob(gen); }

int v[N], had[N], seen[N];
double p[N];
int ct;

int query() {
	if(ct++ == 100) exit(0);
	for(int i = 0; i < n; i++) putchar('0' + v[i]);
	putchar('\n'); fflush(stdout);
	int k;
	scanf("%d", &k);
	if(k == 5001) exit(0);
	return k;
}

int main() {
	int i, j;
	int c = query() - 1;
	had[c] = 1; v[c] = !v[c];
	if(c < 4000) {
		for(i = 0; i < c; i++) v[i] = !v[i];
		c = query() - 1;
		had[c] = 1; v[c] = !v[c];
		for(i = c + 1; i < n; i++) v[i] = !v[i];
	} else for(i = c + 1; i < n; i++) v[i] = !v[i];
	while(true) {
		for(i = 0; had[i]; i++);
		assert(i < c);
		v[i] = !v[i];
		int nc = query() - 1;
		assert(nc != c);
		had[i] = 1;
		if(nc < c) {
			v[i] = !v[i];
			for(i = nc; i < c; i++) had[i] = 1;
		} else {
			if(nc == c + 2) had[c + 1] = 1, v[c + 1] = !v[c + 1];
		}
		c = nc;
		had[c] = 1;
		v[c] = !v[c];
	}
}
