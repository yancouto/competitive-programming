#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
#define x first
#define y second

const int N = 1123456;
pii v[N];
int px[N], py[N], pxi[N], pyi[N], vn;
ll sx[N], sy[N];

int main() {
	int x1, y1, x2, y2, i, n;
	scanf("%d", &n);
	ll Sx = 0, Sy = 0;
	for(i = 0; i < n; i++) {
		scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
		for(int x = x1; x <= x2; x++)
			for(int y = y1; y <= y2; y++) {
				Sx += x;
				Sy += y;
				v[vn] = pii(x, y);
				px[vn] = vn;
				py[vn] = vn;
				vn++;
			}
	}
	sort(v, v + vn);
	sort(px, px + vn, [](int i, int j) { return v[i].x < v[j].x; });
	for(i = 0; i < vn; i++) pxi[px[i]] = i;
	sx[0] = v[px[0]].x;
	for(i = 1; i < vn; i++) sx[i] = sx[i - 1] + v[px[i]].x;
	sort(py, py + vn, [](int i, int j) { return v[i].y < v[j].y; });
	for(i = 0; i < vn; i++) pyi[py[i]] = i;
	sy[0] = v[py[0]].y;
	for(i = 1; i < vn; i++) sy[i] = sy[i - 1] + v[py[i]].y;
	ll best = LLONG_MAX;
	pii bv;
	for(i = 0; i < vn; i++) {
		ll x = v[i].x, y = v[i].y;
		ll tot = 0;
		tot += x * ll(pxi[i]) - (pxi[i]? sx[pxi[i] - 1] : 0);
		tot += (Sx - sx[pxi[i]]) - x * ll(vn - pxi[i] - 1);
		tot += y * ll(pyi[i]) - (pyi[i]? sy[pyi[i] - 1] : 0);
		tot += (Sy - sy[pyi[i]]) - y * ll(vn - pyi[i] - 1);
		if(tot >= best) continue;
		best = tot;
		bv = v[i];
	}
	printf("%lld\n%d %d\n", best, bv.x, bv.y);
}
