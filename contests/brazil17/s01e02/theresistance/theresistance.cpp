#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
typedef long double ld;

const int N = 112;
ld pp[N], prob[N];
int f[N], c[N], id[N][N], mission[N];

ll fat[N];
ll choose(ll n, ll p) {
	if(p < 0 || p > n) return 0;
	return fat[n] / (fat[p] * fat[n - p]);
}


int main() {
	int i, n, s, m, j, bm;
	fat[0] = 1;
	for(i = 1; i <= 15; i++) fat[i] = fat[i - 1] * ll(i);
	scanf("%d %d %d", &n, &s, &m);
	for(i = 0; i < m; i++) scanf("%d", &c[i]);
	for(i = 0; i < m - 1; i++) scanf("%d", &f[i]);
	for(i = 0; i < m - 1; i++)
		for(j = 0; j < c[i]; j++) {
			scanf("%d", &id[i][j]);
			mission[i] |= (1 << id[i][j]);
		}
	ld totbm = 0;
	for(bm = 1; bm < (1 << n); bm++) {
		if(__builtin_popcount(bm) != s) continue;
		prob[bm] = 1;
		for(i = 0; i < m - 1; i++) {
			int x = __builtin_popcount(mission[i] & bm);
			prob[bm] *= choose(x, f[i]) / ld(1 << x);
		}
		totbm += prob[bm];
	}
	vector<int> all_bm;
	for(bm = 1; bm < (1 << n); bm++) {
		if(__builtin_popcount(bm) != s) continue;
		all_bm.pb(bm);
		prob[bm] /= totbm;
		for(j = 0; j < n; j++)
			if((bm >> j) & 1)
				pp[j] += prob[bm];
	}
	ld best = 0;
	for(i = 1; i < (1 << n); i++) {
		if(__builtin_popcount(i) != c[m - 1]) continue;
		ld cur = 0;
		for(int bm : all_bm)
			if((bm & i) == 0)
				cur += prob[bm];
		best = max(best, cur);
	}
	printf("%.20f\n", (double) best);

}
