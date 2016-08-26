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
	num distSqr(ptn o) const { return (*this - o) * (*this - o); }
	bool operator < (ptn o) const { return x < o.x || (x == o.x && y < o.y); }
};
temp inline num cross(ptn a, ptn b, ptn c) { return (c - a) ^ (b - a); }
typedef point<int> pti;
pti ps[1009];
pti x;
bool cmp(pti a, pti b) {
	int v = cross(x, a, b);
	if(v) return v > 0;
	return a.distSqr(x) < b.distSqr(b);
}

int main() {
	int i, n, j, t = 0;
	while(true) {
		scanf("%d", &n);
		if(!n) return 0;
		for(i = 0; i < n; i++)
			scanf("%d %d", &ps[i].x, &ps[i].y);
		int mx = 0;
		for(i = 0; i < n;) {
			swap(*min_element(ps + i, ps + n), ps[i]);
			x = ps[i];
			sort(ps + i + 1, ps + n, cmp);
			int nx = i + 1;
			for(j = i + 1; j < n - 1;) {
				if(cross(x, ps[j], ps[j+1])) { j++; continue; }
				int pnx = nx;
				while(j < n - 1 && !cross(x, ps[j], ps[j+1]))
					ps[nx++] = ps[j++];
				ps[nx++] = ps[j++];
				mx = max(mx, nx - pnx + 1);
			}
			i = nx;
		}
		if(mx < 4) mx = 0;
		printf("Photo %d: %d points eliminated\n", ++t, mx);
	}
}
