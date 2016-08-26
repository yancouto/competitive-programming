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
	bool operator < (point o) const { return x < o.x || (x == o.x && y < o.y); }
};
template<typename num> double distSegSqr(point<num> a, point<num> b, point<num> c) {
	if((b - a) * (c - b) > 0) return b.distSqr(c);
	if((a - b) * (c - a) > 0) return a.distSqr(c);
	double d = (b - a) ^ (c - a);
	return d * d / ((b - a) * (b - a));
}

template <typename num> struct line {
	num a, b, c;
	line() {}
	line(num aa, num bb, num cc) : a(aa), b(bb), c(cc) {}
	line(point<num> s, point<num> e) : a(e.y - s.y), b(e.x - s.x), c(a*s.x + b*s.y) {}
	line pass(point<num> p) { return line(a, b, a*p.x + b*p.y); }
	point<double> inter(line o) {
		double d = a * o.b - o.a * b;
		if(d == 0) return point<double>(0, 0); //fudeu
		return point<double>((o.b * c - b * o.c)/d, (a * o.c - o.a * c)/d);
	}
};
typedef point<int> pointi;
typedef point<double> pointd;
typedef line<int> linei;
typedef line<double> lined;

pointi ps[2009];
int n;
bool lessP(pointi a, pointi b) {
	int v = (a - ps[0]) ^ (b - ps[0]);
	if(v == 0) return ps[0].distSqr(a) < ps[0].distSqr(b);
	return v > 0;
}

int cr(pointi a, pointi b, pointi c) {
	return (b - a) ^ (c - a);
}
int main() {
	int i;
	while(true) {
		scanf("%d", &n);
		if(!n) return 0;
		for(i = 0; i < n; i++)
			scanf("%d %d", &ps[i].x, &ps[i].y);
		int cam = 0;
		int st[2009], p;
		pointi aux[2009];
		while(n > 2) {
			int mi = min_element(ps, ps + n) - ps;
			p = 0;
			swap(ps[0], ps[mi]);	
			sort(ps + 1, ps + n, lessP);
			st[p++] = 0;
			st[p++] = 1;
			st[p++] = 2;
			for(i = 3; i < n; i++) {
				while(p > 2 && cr(ps[st[p-2]], ps[i], ps[st[p-1]]) > 0)
					p--;
				st[p++] = i;
			}
			for(i = 0; i < p; i++)
				aux[i] = ps[st[i]];
			int j = 0;
			for(i = 0; i < n; i++) {
				if(i == st[j]) j++;
				else ps[i - j] = ps[i];
			}
			n -= p;
			int a = 0;
			for(i = 1; i < p - 1; i++)
				a += (aux[i] - aux[0]) ^ (aux[i+1] - aux[0]);
			if(a) cam++;
		}
		if(cam & 1) puts("Take this onion to the lab!");
		else puts("Do not take this onion to the lab!");
	}
}
