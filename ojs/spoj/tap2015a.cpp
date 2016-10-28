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

typedef double num;

struct pt {
	num x, y;
	pt() {}
	pt(num a, num b) : x(a), y(b) {}
	pt operator + (const pt &o) const { return pt(x + o.x, y + o.y); }
	pt operator - (const pt &o) const { return pt(x - o.x, y - o.y); }
	bool operator == (const pt &o) const { return x == o.x && y == o.y; }
};
pt operator * (num x, const pt &o) { return pt(o.x * x, o.y * x); }
pt operator * (const pt &o, num x) { return pt(o.x * x, o.y * x); }
pt operator / (const pt &o, num x) { return pt(o.x / x, o.y / x); }

inline num norm(const pt &x) { return (x.x * x.x + x.y * x.y); }
inline num abs(const pt &x) { return sqrt(x.x * x.x + x.y * x.y); }
inline num x(const pt &o) { return o.x; }
inline num y(const pt &o) { return o.y; }
const int N = 1123;
int X[N], Y[N], r[N];
pt p[N]; int n, ans;

inline int sqr(int x) { return x * x; }
const num eps = 1e-7;

void test(pt a) {
	int ct = 0;
	for(int i = 0; i < n; i++)
		if(norm(p[i] - a) <= sqr(r[i]) + eps)
			ct++;
	ans = max(ans, ct);
}

int main() {
	int i, j;
	while(scanf("%d", &n) != EOF) {
		for(i = 0; i < n; i++) {
			scanf("%d %d %d", &X[i], &Y[i], &r[i]);
			//r[i] = (rand() % 100) + 1;
			p[i] = pt(X[i], Y[i]);
		}
		ans = 1;
		for(i = 0; i < n; i++) test(p[i]);
		for(i = 0; i < n; i++)
			for(j = i + 1; j < n; j++) {
				int dd = sqr(X[i] - X[j]) + sqr(Y[i] - Y[j]);
				if(dd > sqr(r[i] + r[j])) continue;
				if(X[i] == X[j] && Y[i] == Y[j]) continue;
				if(sqrt(dd) + min(r[i], r[j]) < max(r[i], r[j]) + eps) continue;
				num d = abs(p[i] - p[j]);
				if(dd <= sqr(max(r[i], r[j]))) {
					int a = i, b = j;
					if(r[a] < r[b]) swap(a, b);
					num k = (r[a] * r[a] - r[b] * r[b] - d * d) / (2. * d);
					pt dir = (p[b] - p[a]) / abs(p[b] - p[a]);
					pt c = p[b] + k * dir;
					num h = sqrt(sqr(r[b]) - k * k);
					pt ort = pt(-y(dir), x(dir));
					test(c + ort * h);
					test(c - ort * h);
				} else {
					num aux = (d * d + r[i] * r[i] - r[j] * r[j]) / (2. * d);
					pt dir = (p[j] - p[i]) / abs(p[j] - p[i]);
					pt c = p[i] + aux * dir;
					pt ort = pt(-y(dir), x(dir));
					num h = sqrt(sqr(r[i]) - aux * aux);
					test(c + ort * h);
					test(c - ort * h);
				}
			}
		printf("%d\n", ans);
	}
}
