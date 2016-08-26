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
pointi ps[1003];
int seen[1003], cn, n, l;
int main() {
	int i;
	for_tests(t, tt) {
		scanf("%d %d", &n, &l);
		if(tt > 1) putchar('\n');
		for(i = 0; i < n; i++)
			scanf("%d %d", &ps[i].x, &ps[i].y);
		double len = 0;
		int ne, p = 0;
		for(i = 1; i < n; i++)
			if(ps[i] < ps[p])
				p = i;
		int start = p, dis;
		memset(seen, 0, sizeof seen);
		do {
			ne = -1;
			for(i = 0; i < n; i++) {
				 if(seen[i]) continue;
				 if(ne == -1) { ne = i; dis = ps[p].distSqr(ps[i]); continue; }
				 int cr = (ps[ne] - ps[p]) ^ (ps[i] - ps[p]), dd = ps[p].distSqr(ps[i]);
				 if(cr < 0) { ne = i; dis = dd; }
				 else if(cr == 0 && dd > dis) { ne = i; dis = dd; }
			}
			len += sqrt((ps[ne] - ps[p]) * (ps[ne] - ps[p]));
			p = ne;
			seen[p] = true;
		} while(start != p);
		printf("%d\n", int(len + 2 * M_PI * l + 7./12.));
	}
	 return 0;
}
