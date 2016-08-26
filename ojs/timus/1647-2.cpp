#include <bits/stdc++.h>
using namespace std;
template<typename T> inline T abs(T t) { return t < 0? -t : t; }
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
temp inline num cross(ptn a, ptn b, ptn c) { return (c - a) ^ (b - a); }
typedef point<int> pti;
typedef point<double> ptd;

ptd pt[3];
double dist[3][3];

const double eps = 1e-10;
ptd on_tr(double d) {
	ptd a, b; double side;
	while(d > dist[0][1] + dist[1][2] + dist[2][0]) d -= dist[0][1] + dist[1][2] + dist[2][0];
	if(d > dist[0][1] + dist[1][2]) a = pt[2], b = pt[0], d -= dist[0][1] + dist[1][2], side = dist[2][0];
	else if(d > dist[0][1]) a = pt[1], b = pt[2], d -= dist[0][1], side = dist[1][2];
	else a = pt[0], b = pt[1], side = dist[0][1];
	return (b - a) * (d / side) + a;
}
//double per;
double div(ptd a, ptd b) {
	double ar = 0;
	for(int i = 0; i < 3; i++)
		if(cross(a, b, pt[i]) > eps)
			ar += cross(a, b, pt[i]) / 2.;
	return abs(ar);
}
double avg, tot;
const int step = 3000000;
void solve(double le, double ri, int nv) {
	double prev;
	for(int i = 0; i <= step; i++) {
		double ti = i * (ri - le) / step + le;
		ptd p = on_tr(ti);
		ptd o = on_tr(ti + tot / 2.);
		double d = div(p, o);
		if(i > 0 && (d > avg) != (prev > avg)) {
			if(nv == 3) {
				puts("YES");
				printf("%.15f %.15f\n", p.x, p.y);
				printf("%.15f %.15f\n", o.x, o.y);
				exit(EXIT_SUCCESS);
			}
			solve((i - 1) * (ri - le) / step + le, ti, nv + 1);
		}
		prev = d;
	}
}

pti pp[3];

int main() {
	int i, j;
	for(i = 0; i < 3; i++) {
		scanf("%d %d", &pp[i].x, &pp[i].y);
		pt[i].x = pp[i].x;
		pt[i].y = pp[i].y;
	}
	for(i = 0; i < 3; i++)
		for(j = i; j < 3; j++)
			dist[i][j] = dist[j][i] = real(sqrt<double>(pp[i].distSqr(pp[j])));
	tot = dist[0][1] + dist[1][2] + dist[2][0];
	avg = abs(cross(pt[0], pt[1], pt[2])) / 4.;
	solve(0, dist[0][1] + dist[1][2], 1);
	puts("NO");
}
