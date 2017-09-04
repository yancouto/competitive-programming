#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define pb push_back

const double eps = 2e-7;
const int N = 19;
int ts;
ll m, s, h;

double sq (double x) {
	return x*x;
}

double bhas (double a, double b, double c, bool k) {
	double delta = b*b - 4.*a*c;
	if (delta < 0) return 0./0.;
	double x = - b;
	if (k)
		x += sqrt(delta);
	else
		x -= sqrt(delta);
	return x / (2. * a);
}

void print (int q, double x, bool swp) {
	if (swp) x = 100. - x;
	while (q--)
		printf("%.20f ", x);
}

bool go (int z, int e, int c) {
	ll n = z + e + c + 1;
	double s = ::s*::s*n;
	double cm = h * ll(e) + 100ll * ll(c);
	double x = n*m - cm;

	if (x < -eps || x > 100. + eps)
		return 0;

	int lt = z + e + (x + eps < h);
	int leq = z + e + (x < h + eps);
	if (lt >= (n+1)/2 || leq < (n+1)/2)
		return 0;

	double cs = (x-m)*(x-m);
	cs += m*m*ll(z);
	cs += (h-m)*(h-m)*ll(e);
	cs += (100ll-m)*(100ll-m)*ll(c);
	
	if (cs < eps)
		return 0;

	if (cs + eps < s)
		return 0;

	// aproxima geral pra mediana 
	// cuidado com o swap
	bool swp = 0;
	ll f = h; int a = e;
	ll g = 100 - h; int b = 0;

/*
	if (f > g) {
		swp = 1;
		swap(f, g);
		swap(a, b);
		swap(z, c);
		x = 100. - x;
	}
*/

	while (z && c) {
		z--; c--;
		double bcs = cs - sq(100ll);
		double ncs = bcs + sq(g-m) + sq(f-m);

		if (ncs < s + eps) {
			for (int k = 0; k < 2; k++) {
				double d = bhas(2, -200, bcs + 2ll * m * m - 200ll * m + 10000ll - s, k);

				if (d == 0./0. || d > f + eps)
					continue;
				double ccs = bcs + sq(d - m) + sq(100ll - d - m);

				if (abs(ccs - s) < eps) {
					print(z, 0, swp);
					print(a, f, swp);
					print(b, g, swp);
					print(c, 100, swp);
					print(1, d, swp);
					print(1, d, !swp);
					print(1, x, swp);
					return 1;
				}
			}
		}

		a++; b++;
		cs = ncs;
	}

	vector<double> v;
	v.reserve(n);
	for (int i = 0; i < a; i++)
		v.pb(f);
	for (int i = 0; i < b; i++)
		v.pb(g);
	v.pb(x);
	sort(v.begin(), v.end());

	double dd;
	do {
		dd = 0;
		for (int k = 0; k < 2; k++) {
			int l = 0;
			int r = n/2 - 1;
			if (k) {
				l += n/2 + 1;
				r += n/2 + 1;
			}

			double d = v[r] - v[l];
			dd = max(dd, d);

			double md = (v[l] + v[r])*.5;

			double ncs = cs - sqrt(v[l] - m) - sqrt(v[r] - m) + 2.*sqrt(md - m);
			if (ncs < s + eps) {
				double lo = 0., hi = 1.;
				int qs = 70;
				double bcs = cs - sq(v[l] - m) - sq(v[r] - m);
				while (qs--) {
					double alp = (lo + hi)*.5;
					double p = v[l] * alp + v[r] * (1. - alp);
					double q = v[l] * (1. - alp) + v[r] * alp;

					double cur = bcs + sq(p - m) + sq(q - m);
					if (cur < s)
						hi = alp;
					else
						lo = alp;
				}
				
				double alp = lo;
				double p = v[l] * alp + v[r] * (1. - alp);
				double q = v[l] * (1. - alp) + v[r] * alp;

				v[l] = p; v[r] = q;
				for (int i = 0; i < n; i++)
					printf("%.20f ", v[i]);
				printf("\n");
				return 1;
			} else {
				cs = ncs;
				v[l] = v[r] = md;
				sort(v.begin(), v.end());
			}
		}
	} while (dd > eps);
	return 0;
}

int main () {
#ifdef ONLINE_JUDGE
	freopen(, "r", stdin);
	freopen(, "w", stdout);
#endif

	scanf("%d", &ts);
	while (ts--) {
		scanf("%lld %lld %lld", &m, &s, &h);

		if (m == h && s == 0) {
			printf("%lld\n", m);
			continue;
		}

		bool ok = 0;
		for (int n = 3; ok && n <= N; n += 2) {
			for (int ze = 0; ok && ze <= n && ze <= n; ze++) {
				for (int z = 0; ok && z < ze; z++)
					ok = go(z, ze - z, n - ze - 1);
			}
		}

		printf("\n");
	}
}
