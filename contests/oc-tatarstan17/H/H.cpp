#include <bits/stdc++.h>
using namespace std;

inline bool bet(int a, int b, int c) { return a <= b && b <= c; }
inline int side(int a, int b, int c) { return (b > c) - (b < a); }

inline int min0(int a, int b) {
	if(a < 0 && b < 0) return INT_MAX;
	if(a < 0) return b;
	if(b < 0) return a;
	return min(a, b);
}

const int N = 112345;
int p[N], q[N], c[N], mrk[N], more[N], sum[N];

int main() {
	int i, j, k, n, m;
	scanf("%d %d", &n, &m);
	scanf("%d %d", &p[0], &p[n]);
	for(i = 1; i <= n - 1; i++)
		scanf("%d %d", &c[i], &p[i]), q[i] = m + 1 - p[i];
	int tot = 0;
	for(i = 1; i <= n - 1; i++) {
		if(c[i] == 1 || c[i - 1] == 2) continue;
		for(j = i; c[j + 1] == 2; j++);
		int a = p[i - 1], b = p[j + 1];
		if(a > b) swap(a, b);
		vector<int> P;
		for(k = i; k <= j; k++) {
			if(bet(a, p[k], b) || bet(a, q[k], b)) continue;
			P.push_back(k);
			if(side(a, p[k], b) == side(a, q[k], b)) mrk[k] = side(a, p[k], b);
			//printf("mrk[%d] = %d\n", k, mrk[k]);
		}
		if(P.empty()) continue;
		sort(P.begin(), P.end(), [b](int i, int j) { return min0(p[i] - b, q[i] - b) < min0(p[j] - b, q[j] - b); });
		for(k = P.size() - 1; k >= 0; k--) {
			more[k] = (mrk[P[k]] == 1) || (k < P.size() - 1 && more[k + 1]);
			if(!more[k]) sum[k] = max(min0(a - p[P[k]], a - q[P[k]]), (k < P.size() - 1? sum[k + 1] : INT_MIN));
		}
		int mn = INT_MAX;
		if(!more[0]) mn = sum[0];
		int lf = 0;
		for(k = 0; k < P.size() && mrk[P[k]] != -1; k++) {
			lf = max(lf, min0(p[P[k]] - b, q[P[k]] - b));
			//printf("lf %d sum[%d] = %d\n", lf, k+1, sum[k+1]);
			if(k + 1 < P.size() && more[k + 1]) continue;
			else {
				mn = min(mn, lf + (k + 1 < P.size()? sum[k + 1] : 0));
				//printf("new mn %d\n", mn);
			}
		}
		assert(mn != INT_MAX);
		tot += 2 * mn;
	}
	c[0] = c[n] = 1;
	for(i = 0; i < n; ) {
		for(j = i + 1; c[j] != 1; j++);
		tot += abs(p[j] - p[i]);
		i = j;
	}
	printf("%d\n", tot);
}
