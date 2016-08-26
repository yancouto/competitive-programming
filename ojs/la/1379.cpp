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
pti ps[1002];
int main() {
	int i, n, j, t = 0;
	srand(time(NULL)); rand(); rand();
	while(true) {
		scanf("%d", &n);
		if(!n) return 0;
		for(i = 0; i < n; i++)
			scanf("%d %d", &ps[i].x, &ps[i].y);
		int mx = 0;
		for(j = 0; j < 60000; j++) {
			int a = rand() % n, b = rand() % n;
			if(a == b) b = (a + 1) % n;
			int ct = 0;
			for(i = 0; i < n; i++)
				if(!cross(ps[a], ps[b], ps[i]))
					ct++;
			mx = max(mx, ct);
		}
		if(mx < 4) mx = 0;
		printf("Photo %d: %d points eliminated\n", ++t, mx);
	}
}
