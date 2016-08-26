#include <bits/stdc++.h>
using namespace std;
#define x first
#define y second
typedef unsigned long long ull;
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
template<typename T> inline T abs(T t) { return t < 0? -t : t; }
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }

pii p[1009];
int st[1009], sn;

int cross(pii b, pii c) {
	return b.x * c.y - b.y * c.x;
}

pii operator - (pii a, pii b) {
	return pii(a.x - b.x, a.y - b.y);
}

int cross(pii a, pii b, pii c) {
	return cross(b - a, c - a);
}

double norm(pii a) {
	return sqrt(a.x * a.x + a.y * a.y);
}

int main() {
	for_tests(t, tt) {
		if(tt != 1) putchar('\n');
		int i, n, l;
		scanf("%d %d", &n, &l);
		for(i = 0; i < n; i++)
			scanf("%d %d", &p[i].x, &p[i].y);
		sort(p, p + n); sn = 0;
		st[sn++] = 0;
		for(i = 1; i < n; i++) {
			while(sn >= 2 && cross(p[st[sn - 2]], p[st[sn - 1]], p[i]) >= 0)
				sn--;
			st[sn++] = i;
		}
		int k = sn;
		for(i = n - 2; i >= 0; i--) {
			while(sn >= k + 1 && cross(p[st[sn - 2]], p[st[sn - 1]], p[i]) >= 0)
				sn--;
			st[sn++] = i;
		}
		sn--;
		double w = norm(p[st[0]] - p[st[sn - 1]]);
		for(i = 0; i < sn - 1; i++)
			w += norm(p[st[i]] - p[st[i + 1]]);
		printf("%.0f\n", w + 2. * double(l) * acos(-1));
	}
}
