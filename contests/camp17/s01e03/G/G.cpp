#include <bits/stdc++.h>
using namespace std;
#define h first
#define r second
typedef long long ll;
typedef pair<double, double> pdd;
#define pb push_back
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }
#ifdef ONLINE_JUDGE
#	define debug(args...) {}
#else
#	define debug(args...) fprintf(stderr, args)
#endif

int n;

pdd p[2123];
const double pi = acos(-1);
double l[2123], r[2123];

int main() {
	int i, j;
	scanf("%d", &n);
	for(i = 0; i < n; i++) scanf("%lf %lf", &p[i].h, &p[i].r), p[i].r *= 14.;
	sort(p, p + n);
	for(i = 0; i < n; i++) l[i] = max(p[i].h - p[i].r, 0.), r[i] = p[i].h + p[i].r;
	for(i = 0; i < n; i++) {
		for(j = 0; j < i; j++)
			if(p[i].h - p[i].r <= p[j].h + p[j].r) {
				// ver se alguem cobre o outro total
				if(p[i].h - p[i].r < p[j].h - p[j].r - 1e-9) { r[j] = l[j] - 1; continue; }
				if(p[j].h + p[j].r > p[i].h + p[i].r + 1e-9) { r[i] = l[i] - 1; continue; }
				double d = p[i].h - p[j].h;
				double x = (d * d + p[i].r * p[i].r - p[j].r * p[j].r) / (2. * d);
				l[i] = max(l[i], p[i].h - x);
				r[j] = min(r[j], p[i].h - x);
			}
	}
	double tot = 0;
	for(i = 0; i < n; i++) {
		if(r[i] < l[i]) continue;
		if(r[i] <= p[i].h) { double L = l[i], R = r[i]; l[i] = p[i].h + (p[i].h - R); r[i] = p[i].h + (p[i].h - L); }
		if(l[i] >= p[i].h) { tot += 2. * pi * p[i].r * (p[i].h + p[i].r - l[i]) - 2. * pi * p[i].r * (p[i].h + p[i].r - r[i]); }
		else {
			tot += 2. * pi * p[i].r * p[i].r - 2. * pi * p[i].r * (p[i].h + p[i].r - r[i]); // top
			tot += 2. * pi * p[i].r * p[i].r - 2. * pi * p[i].r * (p[i].r - (p[i].h - l[i])); // bot
		}
	}
	printf("%.10f\n", tot);
	
}
