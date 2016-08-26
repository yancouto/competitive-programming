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
};
temp inline num cross(ptn a, ptn b, ptn c) { return (c - a) ^ (b - a); }
temp inline bool betweenSeg(ptn a, ptn b, ptn c) { return cross(a, b, c) == 0 && ((b - c) * (a - c) < 0); }
inline int sign(int x) { return (x > 0) - (x < 0); }
temp bool intersectSeg(ptn a, ptn b, ptn c, ptn d) {
	if(betweenSeg(a, b, c) || betweenSeg(a, b, d) || betweenSeg(c, d, a) || betweenSeg(c, d, b)) return true;
	int c1 = sign(cross(a, b, c)), c2 = sign(cross(a, b, d));
	int c3 = sign(cross(c, d, a)), c4 = sign(cross(c, d, b));
	if(c1 && c1 == -c2 && c3 && c3 == -c4) return true;
	return false;
}

typedef point<int> pti;
typedef point<double> ptd;
const int N = 120;
pti p[N];

int memo[N][N];
bool ok[N][N];
int solve(int i, int j) {
	if(j - i < 2) return 0;
	int &r = memo[i][j];
	if(r != -1) return r;
	r = INT_MAX;
	for(int k = i + 1; k < j; k++)
		if(ok[i][k] && ok[k][j])
			r = min(r, max(max(solve(i, k), solve(k, j)), abs(cross(p[i], p[k], p[j]))));
	return r;
}

int main() {
	int i, j, k, n;
	for_tests(t, tt) {
		scanf("%d", &n);
		memset(ok, 0, sizeof ok);
		memset(memo, -1, sizeof memo);
		for(i = 0; i < n; i++)
			scanf("%d %d", &p[i].x, &p[i].y), ok[i][(i + 1) % n] = true, ok[(i + 1) % n][i] = true, p[i].x *= 2, p[i].y *= 2;
		for(i = n; i < 2*n; i++)
			p[i] = p[i - n];
		for(i = 0; i < n; i++)
			for(j = i + 2; j < n; j++) {
				for(k = 0; k < n; k++)
					if(intersectSeg(p[i], p[j], p[k], p[k + 1]))
						break;
				if(k < n) break;
				pti x = (p[i] + p[j]) / 2;
				int r = sign(cross(p[0], p[1], x));
				for(k = 1; k < n; k++)
					if(r != sign(cross(p[k], p[k + 1], x)))
						break;
				if(k == n) ok[i][j] = ok[j][i] = true;
			}
		for(i = 0; i < 2*n; i++)
			for(j = 0; j < 2*n; j++)
				ok[i][j] = ok[i%n][j%n];
		for(i = 0; i < 2*n; i++)
			p[i].x /= 2, p[i].y /= 2;
		int best = INT_MAX;
		for(i = 0; i < n; i++)
			for(j = i + 1; j < n; j++) {
				if(!ok[i][j]) continue;
				best = min(best, max(solve(i, j), solve(j, i + n)));
			}
		printf("%.1f\n", best / 2.);
	}
}
