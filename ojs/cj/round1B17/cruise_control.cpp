#include <bits/stdc++.h>
using namespace std;
#define k first
#define s second
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)

pii h[112345];

double inter(int i, int j) {
	double t = double(h[j].k - h[i].k) / (h[i].s - h[j].s);
	assert(t >= 0);
	return h[i].k + h[i].s * t;
}

int main() {
	int i, d, n;
	for_tests(t, tt) {
		scanf("%d %d", &d, &n);
		for(i = 0; i < n; i++)
			scanf("%d %d", &h[i].k, &h[i].s);
		sort(h, h + n);
		int lst = n - 1;
		for(i = n - 2; i >= 0; i--) {
			if(h[i].s <= h[lst].s) lst = i;
			else if(inter(i, lst) > d) lst = i;
		}
		printf("Case #%d: %.10f\n", tt, double(d) / (double(d - h[lst].k) / h[lst].s));
	}
}
