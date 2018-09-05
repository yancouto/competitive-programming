#include <bits/stdc++.h>
using namespace std;

typedef long double dbl;
typedef pair<int, int> pii;
#define fst first
#define snd second

dbl sq(dbl x) { return x * x; }

pii a[112345];

int main() {
	int i, n;
	scanf("%d", &n);
	dbl v = 0;
	dbl tot = 0;
	for(i = 0; i < n; i++) {
		scanf("%d %d", &a[i].fst, &a[i].snd);
		tot += v * a[i].snd + 0.5L * a[i].fst * sq(a[i].snd);
		v += dbl(a[i].fst) * a[i].snd;
	}
	sort(a, a + n, greater<pii>());
	dbl def = tot;
	v = tot = 0;
	for(i = 0; i < n; i++) {
		tot += v * a[i].snd + 0.5L * a[i].fst * sq(a[i].snd);
		v += dbl(a[i].fst) * a[i].snd;
	}
	printf("%.1f\n", double(tot - def));
}
