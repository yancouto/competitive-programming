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
typedef point<int> pointi;
pointi ps[10]; int n, m;
pointi aux[10]; int auxn;

double convex(int bm) {
	int i; auxn = 0;
	for(i = 0; i < n; i++)
		if((1 << i) & bm)
			aux[auxn++] = ps[i];
	int p = min_element(aux, aux + auxn) - aux;
	for(i = 2; i < auxn; i++)
		if((aux[i] - aux[0]) ^ (aux[i] - aux[1]))
			break;
	if(i >= auxn) {
		int md = 0;
		for(i = 0; i < auxn; i++)
			md = max(md, aux[p].distSqr(aux[i]));
		return 2*sqrt(md) + 2 * M_PI * m;
	}
	int start = p;
	int seen[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
	double len = 0;
	do {
		int ne = -1, dis;
		for(i = 0; i < auxn; i++) {
			if(seen[i] || i == p) continue;
			if(ne == -1) { ne = i; dis = aux[p].distSqr(aux[i]); }
			int cr = (aux[ne] - aux[p]) ^ (aux[i] - aux[p]), dd = aux[p].distSqr(aux[i]);
			if(cr < 0 || (cr == 0 && dd > dis)) { ne = i; dis = dd; }
		}
		len += sqrt(dis);
		p = ne;
		seen[p] = true;
	} while(start != p);
	return len + 2 * M_PI * m;
}

double memo[600];
double solve(int bm) {
	if(memo[bm] > -.5) return memo[bm];
	double ret = convex(bm);
	for(int i = 1; i < bm; i++) {
		if((i | bm) != bm) continue;
		ret = min(ret, solve(i) + solve(bm ^ i));
	}
	return memo[bm] = ret;
}

int main() {
	int i, t = 0;
	while(true) {
		scanf("%d %d", &n, &m);
		if(n == 0) return 0;
		for(i = 0; i < n; i++)
			scanf("%d %d", &ps[i].x, &ps[i].y);
		for(i = 0; i < (1 << n); i++)
			memo[i] = -1;
		printf("Case %d: length = %.2f\n", ++t, solve((1 << n) - 1));
	}
}
