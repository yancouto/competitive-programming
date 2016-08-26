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
double tot;

pti pp[3];
bool ok;

double go(int i) {
	double x = 4;
	double a = dist[i][(i+1)%3], b = dist[i][(i+2)%3];
	double p = tot / 2.;
	double d = p * p - 2 * a * b;
	if(abs(d) <= eps) d = 0;
	if(d < 0) return -1;
	d = sqrt(d);
	double l = (p + d) / 2.;
	if(l < a + eps && (p - l) < b + eps) return l;
	l = p - l;
	if(l < a + eps && (p - l) < b + eps) return l;
	l = (p - d) / 2.;
	if(abs(l) <= eps) l = 0;
	if(l >= 0 && l < a + eps && (p - l) < b + eps) return l;
	l = p - l;
	if(l >= 0 && l < a + eps && (p - l) < b + eps) return l;
	return -1;
}

ptd on_tr(double d) {
	ptd a, b; double side;
	while(d > tot + eps) d -= tot;
	if(d > dist[0][1] + dist[1][2] + eps) a = pt[2], b = pt[0], d -= dist[0][1] + dist[1][2], side = dist[2][0];
	else if(d > dist[0][1] + eps) a = pt[1], b = pt[2], d -= dist[0][1], side = dist[1][2];
	else a = pt[0], b = pt[1], side = dist[0][1];
	return (b - a) * (d / side) + a;
}

int main() {
	int i, j;
	for(i = 0; i < 3; i++) {
		scanf("%d %d", &pp[i].x, &pp[i].y);
		pt[i].x = pp[i].x;
		pt[i].y = pp[i].y;
	}
	for(i = 0; i < 3; i++)
		for(j = i; j < 3; j++)
			dist[i][j] = dist[j][i] = sqrt(pp[i].distSqr(pp[j]));
	tot = dist[0][1] + dist[1][2] + dist[2][0];
	double d = 0;
	ok = false;
	for(i = 0; i < 3; i++) {
		double l = go(i);
		if(l >= -.5) {
			ptd pa = on_tr(l), pb = on_tr(l + tot / 2.);
			puts("YES");
			printf("%.15f %.15f\n", pa.x, pa.y);
			printf("%.15f %.15f\n", pb.x, pb.y);
			return 0;
		}
		d += dist[i][(i+1)%3];
	}
	puts("NO");
}
