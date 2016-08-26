#include <bits/stdc++.h>
using namespace std;
#define x first
#define y second
typedef unsigned long long ull;
typedef long long ll;
typedef pair<ull, ull> pti;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
template<typename T> inline T abs(T t) { return t < 0? -t : t; }
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }

inline ull sqr(ull x) { return x * x; }
inline ull dist(pti p) { return sqr(p.x) + sqr(p.y); }

struct qu {
	ull a, b, c;
	int i;
	bool operator < (const qu &o) const {
		if(a != o.a) return a < o.a;
		if(b != o.b) return b < o.b;
		return c < o.c;
	}
};

pti p[3009];
qu q[3009];
int ct[3009], ans[3009];

int main() {
	freopen("astronomy.in", "r", stdin);
	freopen("astronomy.out", "w", stdout);
	int i, n, m, j;
	while(scanf("%d", &n) != EOF && n) {
		for(i = 0; i < n; i++)
			scanf("%I64u %I64u", &p[i].x, &p[i].y);
		sort(p, p + n, [](pti a, pti b) { return dist(a) < dist(b); });
		scanf("%d", &m);
		for(i = 0; i < m; i++) {
			scanf("%I64u %I64u %I64u", &q[i].a, &q[i].b, &q[i].c);
			if(q[i].a > q[i].b) swap(q[i].a, q[i].b);
			q[i].i = i;
		}
		sort(q, q + m);
		for(i = 0; i < n; i++)
			for(j = i + 1; j < n; j++) {
				qu qi = {dist(p[i]), dist(p[j]), sqr(p[i].x - p[j].x) + sqr(p[i].y - p[j].y)};
				auto ra = equal_range(q, q + m, qi);
				ct[ra.first - q]++;
				ct[ra.second - q]--;
			}
		for(i = 0; i < m; i++) {
			if(i) ct[i] += ct[i - 1];
			ans[q[i].i] = ct[i];
		}
		for(i = 0; i < m; i++)
			printf("%d\n", ans[i]);
	}
}
