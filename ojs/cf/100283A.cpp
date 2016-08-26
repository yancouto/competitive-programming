#include <bits/stdc++.h>
using namespace std;
int a[1009], mx, n;
const double eps = 1e-8, pi = acos(-1);
bool pos(double r) {
	double cur = 0.;
	for(int i = 0; i < n; i++) {
		double s = a[i] / (2. * r);
		double al = asin(s);
		assert(al >= 0.);
		cur += al;
	}
	return cur <= pi;
}

int main() {
	freopen("zeriba.in", "r", stdin);
	int tn, i;
	scanf("%d", &tn);
	for(int tt = 1; tt <= tn; tt++) {
		scanf("%d", &n);
		int tot = 0; mx = 0;
		for(i = 0; i < n; i++) {
			scanf("%d", &a[i]);
			tot += a[i];
			mx = max(mx, a[i]);
		}
		printf("Case %d: ", tt);
		if(mx * 2 >= tot) { puts("can't form a convex polygon"); continue; }
		double l = mx / 2., r = 10000000.;
		while(r - l > eps) {
			double m = (l + r) / 2;
			if(pos(m)) r = m;
			else l = m;
		}
		printf("%.4f\n", (l + r) / 2.);
	}
}
