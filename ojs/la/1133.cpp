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
temp inline bool betweenSeg(ptn a, ptn b, ptn c) { return cross(a, b, c) == 0 && ((b - c) * (a - c) < 0); }
temp double distSegSqr(ptn a, ptn b, ptn c) {
	if((b - a) * (c - b) > 0) return b.distSqr(c);
	if((a - b) * (c - a) > 0) return a.distSqr(c);
	double d = (b - a) ^ (c - a);
	return d * d / ((b - a) * (b - a));
}
inline int sign(int x) { return (x > 0) - (x < 0); }
temp bool intersectSeg(ptn a, ptn b, ptn c, ptn d) {
	if(betweenSeg(a, b, c) || betweenSeg(a, b, d) || betweenSeg(c, d, a) || betweenSeg(c, d, b)) return true;
	if((sign(cross(a, b, c)) * sign(cross(a, b, d))) == -1 && (sign(cross(c, d, a)) * sign(cross(c, d, b))) == -1) return true;
	return false;
}

typedef point<int> pti;
const int N = 110;
pti p[N];
bool ok[N][N];


int memo[N][N];
int solve(int i, int j) {
	if(j - i < 2) return 0;
	int &r = memo[i][j];
	if(r != -1) return r;
	r = INT_MAX;
	for(int k = i + 1; k < j; k++)
		if(ok[i][k] && ok[k][j])
			r = min(r, max(max(solve(i, k), solve(k, j)), abs(cross(p[i], p[j], p[k]))));
	return r;
}

bool in_pol(int n, pti x) {
	int all = 0;
	for(int k = 0; k < 3; k++) {
		pti o;
		do	o = pti(rand() % 50000, rand() % 50000);
		while(o.x <= 20000 && o.y <= 20000);
		bool in = false;
		for(int i = 0; i < n; i++)
			if(intersectSeg(x, o, p[i], p[i + 1]))
				in = !in;
		all += in;
	}
	return all >= 2;
}

int main() {
	srand(time(NULL));
	int i, j, n, k;
	for_tests(t, tt) {
		memset(ok, 0, sizeof ok);
		memset(memo, -1, sizeof memo);
		scanf("%d", &n);
		for(i = 0; i < n; i++)
			scanf("%d %d", &p[i].x, &p[i].y), p[i] = p[i] * 2;
		for(i = n; i < 2 * n; i++)
			p[i] = p[i - n];
		for(i = 0; i < n; i++) ok[i][(i + 1) % n] = ok[(i + 1) % n][i] = true;
		for(i = 0; i < n; i++)
			for(j = i + 2; j < n; j++) {
				for(k = 0; k < n; k++)
					if(intersectSeg(p[i], p[j], p[k], p[k + 1]))
						break;
				if(k < n) continue;
				if(in_pol(n, (p[i] + p[j]) / 2)) ok[i][j] = ok[j][i] = true;
			}
		for(i = 0; i < 2 * n; i++)
			for(j = 0; j < 2 * n; j++)
				ok[i][j] = ok[i%n][j%n];
		for(i = 0; i < 2 * n; i++) p[i] = p[i] / 2;
		int ans = solve(0, n - 1);
		for(i = 0; i < n; i++)
			for(j = i + 1; j < n; j++)
				if(ok[i][j])
					ans = min(ans, max(solve(i, j), solve(j, i + n)));
		for(i = 0; i < n; i++)
			assert(solve(i, i + 2) == abs(cross(p[i], p[i + 1], p[i + 2])));
		printf("%d%s\n", ans / 2, ((ans & 1)? ".5" : ".0"));
	}
}
