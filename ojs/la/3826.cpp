#include <cstdio>
#include <algorithm>
using namespace std;
typedef unsigned long long ull;

int mdc(int a, int b) {
	if(a < b) return mdc(b, a);
	if(a % b == 0) return b;
	return mdc(b, a % b);
}

int a[500], b[500], c[500];
int as = 0;

void pre() {
	for(int i = 1; i < 1000; i++)
		for(int j = i + 1; j < 1000; j++) {
			if(mdc(i, j) == 1 && !((i & 1) && (j & 1))) {
				int aa = j * j - i * i;
				int bb = 2 * i * j;
				int cc = i * i + j * j;
				if(aa > 1000 || bb > 1000) continue;
				a[as] = aa;
				b[as] = bb;
				c[as++] = cc;
			}
		}
	a[as] = 1;
	b[as] = 0;
	c[as++] = 1;
}

int h, w;
ull go(int i) {
	int aa = a[i], bb = b[i], cc = c[i];
	ull tot = 0;
	for(int k = 1; ; k++) {
		int x = aa * k, y = bb * k, z = cc * k;
		if((x >= w || y >= h) && (x >= h || y >= w)) break;
		for(int j = 1; j < z; j++) {
			int r1 = j, r2 = z - j;
			int wid = max(2 * r1, max(2 * r2, r1 + r2 + x));
			int hei = max(2 * r1, max(2 * r2, r1 + r2 + y));
			if(wid <= w && hei <= h)
				tot += (w - wid + 1) * (h - hei + 1);
			if(hei <= w && wid <= h)
				tot += (w - hei + 1) * (h - wid + 1);
		}
	}
	if(aa && bb) return 2 * tot; // reflexão
	return tot;
}

int main() {
	pre();
	int t, i, j;
	scanf("%d", &t);
	for(int tt = 1; tt <= t; tt++) {
		scanf("%d %d", &h, &w);
		ull tot = 0;
		for(i = 0; i < as; i++)
			tot += go(i);
		printf("Case %d: %llu\n", tt, tot);
	}
	return 0;
}