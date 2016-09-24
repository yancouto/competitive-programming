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
const int N = 112345;
int a[N], ans[N], nx[N], pr[N], nb[16][N], pb[16][N];
int nxb[20], prb[20], auxl[20], auxr[20];

int main() {
	int i, n, lb, rb, b;
	scanf("%d", &n);
	for(i = 0; i < n; i++) scanf("%d", &a[i]);
	pr[0] = -1;
	for(i = 1; i < n; i++)
		if(a[i - 1] > a[i]) pr[i] = i - 1;
		else pr[i] = pr[i - 1];
	nx[n - 1] = n;
	for(i = n - 2; i >= 0; i--)
		if(a[i + 1] > a[i]) nx[i] = i + 1;
		else nx[i] = nx[i + 1];
	for(i = 0; i < 16; i++) {
		if((a[0] >> i) & 1) pb[i][0] = 0;
		else pb[i][0] = -1;
		if((a[n - 1] >> i) & 1) nb[i][n - 1] = n - 1;
		else nb[i][n - 1] = n;
	}
	for(b = 0; b < 16; b++)
		for(i = 1; i < n; i++)
			if((a[i] >> b) & 1) pb[b][i] = i;
			else pb[b][i] = pb[b][i - 1];
	for(b = 0; b < 16; b++)
		for(i = n - 2; i >= 0; i--)
			if((a[i] >> b) & 1) nb[b][i] = i;
			else nb[b][i] = nb[b][i + 1];
	// GOOOOOOO
	for(i = 0; i < n; i++) {
		int l = pr[i] + 1, r = nx[i] - 1;
		for(b = 0; b < 16; b++)
			nxb[b] = nb[b][i],
			prb[b] = pb[b][i];
		nxb[16] = prb[16] = i;
		sort(nxb, nxb + 17);
		sort(prb, prb + 17, greater<int>());
		int nxbn = unique(nxb, nxb + 17) - nxb;
		int prbn = unique(prb, prb + 17) - prb;
		auxl[0] = auxr[0] = a[i];
		for(lb = 1; lb < prbn; lb++) auxl[lb] = (auxl[lb - 1] | a[prb[lb]]);
		for(rb = 1; rb < nxbn; rb++) auxr[rb] = (auxr[rb - 1] | a[nxb[rb]]);
		for(lb = 0; lb < prbn; lb++)
			for(rb = 0; rb < nxbn; rb++) {
				int sz = nxb[rb] - prb[lb] + 1;
				ans[sz] = max(ans[sz], a[i] + (auxl[lb] | auxr[rb]));
			}
	}
	for(i = 1; i <= n; i++) {
		ans[i] = max(ans[i], ans[i - 1]);
		printf("%d\n", ans[i]);
	}
}
