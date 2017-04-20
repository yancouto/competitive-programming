#include <bits/stdc++.h>
using namespace std;

inline int cr(int x1, int y1, int x2, int y2) {
	return x1 * y2 - x2 * y1;
}
#define x first
#define y second

const int N = 21234;
pair<int, int> p[N];

inline int cross(int a, int b, int c) {
	return cr(p[b].x - p[a].x, p[b].y - p[a].y, p[c].x - p[a].x, p[c].y - p[a].y);
}

int st[N], sn;
int bb(int i, int j, int l, int r) {
	while(l < r) {
		int m = (l + r) / 2;
		if(abs(cross(st[i], st[j], st[m])) <= abs(cross(st[i], st[j], st[m + 1])))
			l = m + 1;
		else
			r = m;
	}
	//printf("bb(%d, %d) = %d (%d)\n", i, j, l, abs(cross(i, j, l)));
	return abs(cross(st[i], st[j], st[l]));
}


int main() {
	int T;
	scanf("%d", &T);
	int i, j, n;
	while(T--) {
		scanf("%d", &n);
		for(i = 0; i < n; i++) scanf("%d %d", &p[i].x, &p[i].y);
		sort(p, p + n);
		sn = 0;
		for(i = 0; i < n; i++) {
			while(sn > 1 && cross(st[sn - 2], st[sn - 1], i) < 0) sn--;
			st[sn++] = i;
		}
		int k = sn - 1;
		for(i = n - 2; i >= 0; i--) {
			while(sn > k + 1 && cross(st[sn - 2], st[sn - 1], i) < 0) sn--;
			st[sn++] = i;
		}
		sn--;
		for(i = sn; i < 2 * sn; i++) st[i] = st[i - sn];
		int mx = 0;
		for(i = 0; i < sn; i++)
			for(j = i + 1; j < sn; j++) {
				int A = 0;
				if(j != i + 1) A += bb(i, j, i + 1, j - 1);
				if(i > 0 || j < sn - 1) A += bb(i, j, j + 1, i + sn - 1);
				mx = max(mx, A);
			}
		if(mx & 1) printf("%d.5\n", mx / 2);
		else printf("%d\n", mx / 2);
	}
}
