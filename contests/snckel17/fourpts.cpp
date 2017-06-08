#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }

#include <cmath>
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
	point<double> rotate(double deg) {
		double cs = cos(deg), sn = sin(deg);
		return point<double>(x*cs - y*sn, x*sn + y*cs);
	}
	num dist_sqr(ptn o) const { return (*this - o) * (*this - o); }
	bool operator < (ptn o) const { return x < o.x || (x == o.x && y < o.y); }
	point<double> toD() { return point<double>(x, y); }
};
typedef point<int> pti;
typedef point<double> ptd;
temp inline num cross(ptn a, ptn b, ptn c) { return (c - a) ^ (b - a); }
// o ponto c esta no segmento [a, b]?
temp inline bool between_seg(ptn a, ptn b, ptn c) { return cross(a, b, c) == 0 && ((b - c) * (a - c) <= 0); }
// sqr dist de c pro segmento [a, b]
temp double dist_seg_sqr(ptn a, ptn b, ptn c) {
	if((b - a) * (c - b) > 0) return b.dist_sqr(c);
	if((a - b) * (c - a) > 0) return a.dist_sqr(c);
	double d = (b - a) ^ (c - a);
	return d * d / ((b - a) * (b - a));
}
temp int sign(num x) { return (x > 0) - (x < 0); }
// [a, b] intersecta [c, d]?
temp bool inter_seg(ptn a, ptn b, ptn c, ptn d) {
	if(between_seg(a, b, c) || between_seg(a, b, d) || between_seg(c, d, a) || between_seg(c, d, b)) return true;
	if((sign(cross(a, b, c)) * sign(cross(a, b, d)) == -1) && (sign(cross(c, d, a)) * sign(cross(c, d, b)) == -1)) return true;
	return false;
}

temp struct line {
	num a, b, c;
	line() {}
	line(num aa, num bb, num cc) : a(aa), b(bb), c(cc) {}
	line(ptn s, ptn e) : a(e.y - s.y), b(s.x - e.x), c(a*s.x + b*s.y) {}
	line pass(ptn p) { return line(a, b, a*p.x + b*p.y); }
	bool parallel(const line &o) const { return a * o.b - o.a * b == 0; }
	point<double> inter(line o) {
		double d = a * o.b - o.a * b;
		if(d == 0) return point<double>(0, 0); // fudeu
		return point<double>((o.b * c - b * o.c)/d, (a * o.c - o.a * c)/d);
	}
};
typedef line<int> lni;
typedef line<double> lnd;
ptd ps[10], st[10];

// convex hull - modifique como necessario
void convex_hull(ptd p[], ptd st[], int n) {
	sort(p, p + n);
	int sn = 0;
	for(int i = 0; i < n; i++) {
		while(sn >= 2 && cross(st[sn - 2], st[sn - 1], p[i]) > 1e-7)
			sn--;
		st[sn++] = p[i];
	}
	int k = sn;
	for(int i = n - 2; i >= 0; i--) {
		while(sn > k && cross(st[sn - 2], st[sn - 1], p[i]) > 1e-7)
			sn--;
		st[sn++] = p[i];
	}
	sn--;
	printf("YES");
	for(int i = 0; i < 3; i++)
		printf(" %.20f %.20f", st[i].x, st[i].y);
	putchar('\n');
		
	// st[0..sn-1] agora tem o convex hull dos pontos p
}
pti pi[10];
const double eps = 1e-7;

int main() {
	int i, a, b, c, d;
	for_tests(tn, tt) {
		for(i = 0; i < 4; i++) scanf("%d %d", &pi[i].x, &pi[i].y);
		for(a = 0; a < 4; a++)
			for(b = 0; b < 4; b++)
				for(c = 0; c < 4; c++) {
					if(a == b || b == c || c == a) continue;
					if(!between_seg(pi[a], pi[b], pi[c])) continue;
					for(d = 0; d < 4; d++) {
						if(d == a || d == b || d == c) continue;
						if(cross(pi[a], pi[b], pi[d]) == 0) {
							if(!between_seg(pi[a], pi[b], pi[d])) continue;
							printf("YES %d %d %d %d %d %d\n", pi[a].x, pi[a].y, pi[b].x, pi[b].y, pi[d].x, pi[d].y);
							goto end;
						} else {
							printf("YES %d %d %d %d %d %d\n", pi[a].x, pi[a].y, pi[b].x, pi[b].y, pi[d].x, pi[d].y);
							goto end;
						}
					}
				}
		for(a = 0; a < 4; a++)
			for(b = a + 1; b < 4; b++) {
				vector<int> cd;
				for(c = 0; c < 4; c++)
					if(c != a && c != b) cd.pb(c);
				c = cd[0];
				d = cd[1];
				if(cross(pi[b], pi[c], pi[d]) > 0) swap(c, d);
				if(sign(cross(pi[a], pi[b], pi[c])) != sign(cross(pi[a], pi[b], pi[d]))) continue;
				ptd A = pi[a].toD(), B = pi[b].toD(), C = pi[c].toD(), D = pi[d].toD();
				ptd BD = (D - B) / sqrt(D.dist_sqr(B));
				ptd E = D;
				if(((pi[b] - pi[a]) ^ (pi[d] - pi[c])) == 0) E = E + BD * 3.391732;
				ptd I = lnd(A, B).inter(lnd(E, C));
				if(((I - A) * (I - B)) < -eps) { puts("NO"); goto end; }
				ps[0] = A; ps[1] = B; ps[2] = C; ps[3] = D; ps[4] = E; ps[5] = I;
				convex_hull(ps, st, 5);
				goto end;
			}
end:;
	}
}
