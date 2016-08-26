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
int ct[N], qu;
int bk[103][N];
int ans[103];

int query() {
	if(qu++ == 100) exit(0);
	for(int i = 0; i < n; i++) putchar('0' + v[i]), bk[qu][i] = v[i];
	putchar('\n'); fflush(stdout);
	scanf("%d", &ans[qu]);
	if(ans[qu] == 5001) exit(0);
	return ans[qu];
}

int main() {
	int i, j;
	int c = query() - 1;
	had[c] = 1; v[c] = !v[c];
	for(i = 0; i < n; i++) p[i] = .5, ct[i] = 1;
	for(j = 0; j < 10; j++) {
		for(i = 0; i < n; i++) if(!had[i]) v[i] = (P() <= .5);
		c = query() - 1;
		had[c] = 1; v[c] = !v[c];
		double pr = 1999. / c;
		for(i = 0; i < c; i++)
			p[i] = (ct[i] * p[i] + (v[i]? 1. - pr : pr)) / (ct[i] + 1), ct[i]++;
	}
	for(j = 0; j < 7; j++) {
		for(i = 0; i < n; i++) if(!had[i]) v[i] = (P() <= p[i]);
		c = query() - 1;
		had[c] = 1; v[c] = !v[c];
		double pr = 1999. / c;
		for(i = 0; i < c; i++)
			p[i] = (ct[i] * p[i] + (v[i]? 1. - pr : pr)) / (ct[i] + 1), ct[i]++;
	}
	int bs = (max_element(ans + 1, ans + qu) - ans);
	for(i = 0; i < n; i++) if(!had[i]) v[i] = bk[bs][i];
	c = query() - 1;
	had[c] = 1; v[c] = !v[c];
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
