#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll,ll> pii;
#define pb push_back
typedef long double ld;

struct vec {
	ll x, y, z;
	vec operator - (vec o) const { return vec{x - o.x, y - o.y, z - o.z}; }
} v[112];

vec cross(vec a, vec b) {
	return vec{a.y * b.z - b.y * a.z, -(a.x * b.z - b.x * a.z), a.x * b.y - b.x * a.y};
}

ll inner(vec a, vec b) {
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

ld p[112];

int main () {
	int i, n, j;
	scanf("%d", &n);
	for(i = 0; i < n; i++) {
		double p;
		scanf("%lf %lld %lld %lld", &p, &v[i].x, &v[i].y, &v[i].z);
		::p[i] = p;
	}
	ld pf = 0;
	for(int i = 0; i < n; i++)
		for(int j = i + 1; j < n; j++)
			for(int k = j + 1; k < n; k++) {
				vec d = cross(v[j] - v[i], v[k] - v[i]);
				vector<int> R, L;
				//printf("(%d, %d, %d)\n", i, j, k);
				//printf("d = (%lld, %lld, %lld)\n", d.x, d.y, d.z);
				assert(inner(v[i] - v[i], d) == 0);
				assert(inner(v[j] - v[i], d) == 0);
				assert(inner(v[k] - v[i], d) == 0);
				ld spl = 1, spr = 1, npl = 1, npr = 1;
				for(int l = 0; l < n; l++) {
					//if(l == i || l == j || l == k) continue;
					ll sg = inner(d, v[l] - v[i]);
					//printf("sg(%d) = %lld\n", l, sg);
					if(sg > 0) { R.pb(l); spr *= p[l]; npr *= (1. - p[l]); }
					if(sg < 0) { L.pb(l); spl *= p[l]; npl *= (1. - p[l]); }
				}
				ld pr = 1, pl = 1, pa = 1;
				for(int x : R) pr *= (1. - p[x]), pa *= (1. - p[x]);
				for(int x : L) pl *= (1. - p[x]), pa *= (1. - p[x]);

				pf += p[i]*p[j]*p[k]*( (1. - npr)*npl + (1. - npl)*npr);
				//pf += (pl + pr - 2. * pa) * p[i] * p[j] * p[k];
			}

	ld pv = 0;
	ld pb = 1;
	ld pdump = 1;
	for(i = 0; i < n; i++) {
		pdump *= (1 - p[i]);
		ld pp = 1;
		for(j = 0; j < n; j++)
			if(i == j)
				pp *= p[j];
			else
				pp *= (1. - p[j]);
		pv += pp;
		pb -= pp;
	}
	for(i = 0; i < n; i++) {
		for(j = i + 1; j < n; j++) {
			ld pp = 1;
			for(int k = 0; k < n; k++)
				if(k == i || k == j)
					pp *= p[k];
				else
					pp *= (1. - p[k]);
			pv += 2 * pp;
			pb -= pp;
		}
	}
	for(i = 0; i < n; i++) {
		for(j = i + 1; j < n; j++) {
			for(int k = j + 1; k < n; k++) {
				ld pp = 1;
				for(int g = 0; g < n; g++)
					if(g == i || g == j || g == k)
						pp *= p[g];
					else
						pp *= (1. - p[g]);
				pv += 3 * pp;
				pb -= pp;
			}
		}
	}
	pb -= pdump;
	ld pm = 0;
	if (n >= 4)
		pm = (pf/2) + 2.*(pb);
	printf("%.20f\n", double(pv + pm));
}
