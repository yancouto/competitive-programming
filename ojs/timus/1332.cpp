#include <bits/stdc++.h>
using namespace std;
#define temp template<typename num>
#define ptn point<num>
temp struct point {
	num x, y;
	ptn() {}
	ptn(num a, num b) : x(a), y(b) {}
	ptn operator + (ptn o) const { return ptn(x + o.x, y + o.y); }
	ptn operator - (ptn o) const { return ptn(x - o.x, y - o.y); }
	num operator * (ptn o) const { return x * o.x + y * o.y; }
	num operator ^ (ptn o) const { return x * o.y - y * o.x; }
	ptn operator * (num i) const { return ptn(x * i, y * i); }
	ptn operator / (num i) const { return ptn(x / i, y / i); }
	num distSqr(ptn o) const { return (*this - o) * (*this - o); }
};
typedef point<double> ptd;
int r, n;
const int N = 120;
const double eps = 1e-7;
ptd p[N];

int cover(ptd x) {
	int tot = 0;
	for(int i = 0; i < n; i++)
		if(x.distSqr(p[i]) - r * r <= eps)
			tot++;
	return tot;
}

int go(ptd a, ptd b) {
	if(a.distSqr(b) - 4 * r * r >= eps) return 0;
	ptd c = (a + b) / 2.;
	ptd d = b - a;
	d = ptd(-d.y, d.x);
	d = d / sqrt(d * d);
	assert(fabs((b - a) * d) <= eps);
	double h = sqrt(fabs(r * r - a.distSqr(b) / 4.));
	int ans = max(cover(c + (d * h)), cover(c - (d * h)));
	assert(ans >= 2);
	return ans;
}

int ev[40114];
int main() {
	int i, j, R;
	scanf("%d", &n);
	for(i = 0; i < n; i++)
		scanf("%lf %lf", &p[i].x, &p[i].y);
	scanf("%d %d", &R, &r);
	if(R < r) { puts("0"); return 0; }
	if(R == r) { puts("1"); return 0; }
	r = R - r;
	int mx = 1;
	for(i = 0; i < n; i++)
		for(j = i + 1; j < n; j++)
			mx = max(mx, go(p[i], p[j]));
	for(i = 0; i < n; i++)
		mx = max(mx, cover(p[i]));
	printf("%d\n", mx);
}
