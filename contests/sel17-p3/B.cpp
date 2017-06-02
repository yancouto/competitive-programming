#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int n;
const int N = 112345;
int t[N], v[N];

double go(double T) {
	double mx = -1./0., mn = 1./0.;
	for(int i = 0; i < n; i++) {
		double x = (T - t[i]) * double(v[i]);
		mx = max(mx, x);
		mn = min(mn, x);
	}
	return mx - mn;
}

int main() {
	int i, j;
	while(scanf("%d", &n) != EOF && n) {
		for(i = 0; i < n; i++)
			scanf("%d %d", &t[i], &v[i]);
		double l = *max_element(t, t + n), r = 1e11;
		for(j = 0; j < 150; j++) {
			double v1 = go((2. * l + r) / 3.);
			double v2 = go((l + 2. * r) / 3.);
			if(v1 <= v2) r = (l + 2. * r) / 3.;
			else l = (2. * l + r) / 3.;
		}
		printf("%.10f\n", go(l));
	}
}
