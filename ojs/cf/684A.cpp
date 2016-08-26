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

int query() {
	for(int i = 0; i < n; i++) putchar('0' + v[i]);
	putchar('\n'); fflush(stdout);
	int k;
	scanf("%d", &k);
	return k;
}

int main() {
	int i, j;
	for(i = 0; i < n; i++) p[i] = 0.5;
	for(j = 0; j < x; j++) {
		for(i = 0; i < n; i++) v[i] = P() < p[i];
		int c = query() - 1;
		p[c] = (v[c] == 0); had[c] = 1;
		for(i = 0; i < c; i++) {
			if(had[i]) continue;
			double pr = double(k - 1) / c;
			if(v[i]) pr = 1 - pr;
			if(!seen[j]) p[i] = pr, seen[j] = 1;
			else p[i] = sqrt(p[i] * pr);
		}
	}
}
