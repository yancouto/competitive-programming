#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef unsigned long long ull;
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
template<typename T> inline T abs(T t) { return t < 0? -t : t; }
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }

const int N = 112345;
typedef double num;
struct pt {
	num x, y;
	pt() {}
	pt(num a, num b) : x(a), y(b) {}
	pt operator + (pt o) { return pt(x + o.x, y + o.y); }
	pt operator - (pt o) { return pt(x - o.x, y - o.y); }
	pt rotate(double deg) {
		double cs = cos(deg), sn = sin(deg);
		return pt(x*cs - y*sn, x*sn + y*cs);
	}
} p[N];

int main() {
	int i, n, m;
	scanf("%d %d", &n, &m);
	for(i = 0; i < n; i++)
		scanf("%lf %lf", &p[i].x, &p[i].y);
	while(m--) {
		pt a, b;
		scanf("%lf %lf %lf %lf", &a.x, &a.y, &b.x, &b.y);
		pt r = b - a;
		double ang = atan2(r.y, r.x);
		for(i = 0; i < n; i++) {
			pt q = (p[i] - a).rotate(-ang);
			if(q.y >= 0) continue;
			q.y = -q.y;
			p[i] = (q.rotate(ang) + a);
		}
	}
	for(i = 0; i < n; i++)
		printf("%.10f %.10f\n", p[i].x, p[i].y);
}
