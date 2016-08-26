#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef pair<int, int> pii;
typedef unsigned long long ull;
typedef long long ll;
typedef long double ld;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
template<typename T> inline T abs(T t) { return t < 0? -t : t; }
const ull modn = 1000000007;
inline ull mod(ull x) { return x % modn; }
template<typename num> struct point {
	num x, y;
	point() {}
	point(num a, num b) : x(a), y(b) {}
	point operator + (point o) const { return point(x + o.x, y + o.y); }
	point operator - (point o) const { return point(x - o.x, y - o.y); }
	num operator * (point o) const { return x * o.x + y * o.y; }
	num operator ^ (point o) const { return x * o.y - y * o.x; }
	point operator * (num i) const { return point(x * i, y * i); }
	point operator / (num i) const { return point(x / i, y / i); }
	point<double> rotate(double deg) {
		double cs = cos(deg), sn = sin(deg);
		return point<double>(x*cs - y*sn, x*sn + y*cs);
	}
	num distSqr(point o) const { return (*this - o) * (*this - o); }
};
template<typename num> struct seg {
	point<num> a, b;
	seg() {}
	seg(point<num> s, point<num> e) : a(s), b(e) {}
	double distSqr(point<num> c) {
		if((b - a) * (c - b) > 0) return b.distSqr(c);
		if((a - b) * (c - a) > 0) return a.distSqr(c);
		double d = (b - a) ^ (c - a);
		return d * d / ((b - a) * (b - a));
	}
};
typedef point<int> pointi;
typedef seg<int> segi;

pointi inr[102];
pointi out[103];
int ni, no;

double mndist(pointi *p1, int s1, pointi *p2, int s2) {
	double mn = DBL_MAX;
	for(int i = 0; i < s1; i++)
		for(int j = 0; j < s2; j++)
			mn = min(mn, segi(p2[j], p2[(j+1)%s2]).distSqr(p1[i]));
	return mn;
}

int main() {
	int i;
	for_tests(t, tt) {
		scanf("%d", &ni);
		for(i = 0; i < ni; i++)
			scanf("%d %d", &inr[i].x, &inr[i].y);
		scanf("%d", &no);
		for(i = 0; i < no; i++)
			scanf("%d %d", &out[i].x, &out[i].y);
		printf("%.8f\n", sqrt(min(mndist(inr, ni, out, no), mndist(out, no, inr, ni)))/2);
	}
	return 0;
}
