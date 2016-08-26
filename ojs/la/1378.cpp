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

struct rect {
	int x, y, w, h;
	rect() {}
	rect(int x1, int y1, int x2, int y2) {
		x = min(x1, x2);
		y = min(y1, y2);
		w = max(x1, x2) - x;
		h = max(y1, y2) - y;
	}
} rs[1002];

int main() {
	int i, j, k, n, x1, y1, x2, y2, t = 0;
	while(true) {
		scanf("%d", &n);
		if(!n) return 0;
		ll tot = 0;
		for(i = 0; i < n; i++) {
			scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
			rs[i] = rect(x1, y1, x2, y2);
			for(j = 1; ; j++) {
				int nh = rs[i].h - j + 1, nw = rs[i].w - j + 1;
				if(nh <= 0 || nw <= 0) break;
				tot += ll(nh) * nw;
			}
		}
		for(i = 0; i < n; i++)
			for(j = i + 1; j < n; j++) {
				int a = i, b = j;
				if(rs[a].x > rs[b].x) swap(a, b);
				else if(rs[a].x == rs[b].x && rs[a].y < rs[b].y) swap(a, b);
				if(rs[a].y == rs[b].y + rs[b].h || rs[a].y + rs[a].h == rs[b].y) {
					int sz = min(rs[a].x + rs[a].w, rs[b].x + rs[b].w) - rs[b].x - 2;
					int s1 = rs[a].h, s2 = rs[b].h;
					for(k = 2; (sz - k + 1) > 0 && (s1 + s2 - k + 1) > 0; k++)
						tot += (sz - k + 1) * (s1 + s2 - k + 1);
					for(k = 2; (sz - k + 1) > 0 && (s1 - k + 1) > 0; k++)
						tot -= (sz - k + 1) * (s1 - k + 1);
					for(k = 2; (sz - k + 1) > 0 && (s2 - k + 1) > 0; k++)
						tot -= (sz - k + 1) * (s2 - k + 1);
				}
				if(rs[a].x + rs[a].w == rs[b].x) {
					int sz = min(rs[a].y + rs[a].h, rs[b].y + rs[b].h) - max(rs[a].y, rs[b].y) - 2;
					int s1 = rs[a].w, s2 = rs[b].w;
					for(k = 2; (sz - k + 1) > 0 && (s1 + s2 - k + 1) > 0; k++)
						tot += (sz - k + 1) * (s1 + s2 - k + 1);
					for(k = 2; (sz - k + 1) > 0 && (s1 - k + 1) > 0; k++)
						tot -= (sz - k + 1) * (s1 - k + 1);
					for(k = 2; (sz - k + 1) > 0 && (s2 - k + 1) > 0; k++)
						tot -= (sz - k + 1) * (s2 - k + 1);
				}
			}
		printf("Case %d: %lld\n", ++t, tot);
	}
}
