#include <bits/stdc++.h>
using namespace std;
#define x first
#define y second
typedef pair<int, int> pii;
typedef unsigned long long ull;
typedef long long ll;
typedef long double ld;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
template<typename T> inline T abs(T t) { return t < 0? -t : t; }
const ull modn = 1000000007;
inline ull mod(ull x) { return x % modn; }

pii p[100009];
int main() {
	int i, n, mxx, mxy, mnx, mny;
	for_tests(t, tt) {
		scanf("%d", &n);
		mxx = mxy = INT_MIN;
		mnx = mny = INT_MAX;
		for(i = 0; i < n; i++) {
			scanf("%d %d", &p[i].x, &p[i].y);
			mxx = max(mxx, p[i].x); mnx = min(mnx, p[i].x);
			mxy = max(mxy, p[i].y); mny = min(mny, p[i].y);
		}
		for(i = 0; i < n; i++)
			if((p[i].x == mxx || p[i].x == mnx) && (p[i].y == mxy || p[i].y == mny))
				break;
		if(i < n) { printf("1\n%d %c%c\n", i + 1, p[i].y == mxy? 'S' : 'N', p[i].x == mxx? 'W' : 'E'); continue; }
		int m1 = max_element(p, p + n) - p;
		swap(p[0], p[m1]);
		int m2 = max_element(p + 1, p + n) - p;
		swap(p[1], p[m2]);
		if(m2 == m1) m2 = 0;
		puts("2");
		if(p[0].y == p[1].y) { printf("%d NW\n%d SW\n", m1 + 1, m2 + 1); continue; }
		printf("%d %cW\n", m1 + 1, p[1].y < p[0].y? 'S' : 'N');
		printf("%d %cW\n", m2 + 1, p[0].y < p[1].y? 'S' : 'N');
	}
}
