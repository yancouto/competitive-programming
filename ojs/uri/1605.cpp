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
ld p1, p2;
ld n1, n2, w1, w2;

ld memo2[4][4][51][4][51][2];
ld s2(int left, int i, int m1, int j, int m2, bool all) {
	if(left == 0) return !i && !j && !all;
	ld &d = memo2[left][i][m1][j][m2][all];
	if(d > -.5) return d;
	d  = p1 * ((n1 - m1) / n1) * s2(left - 1, i, m1, j, m2, all);
	d += p2 * ((n2 - m2) / n2) * s2(left - 1, i, m1, j, m2, false);
	if(i > 0) d += p1 * (m1 / n1) * s2(left - 1, i - 1, m1 - 1, j, m2, all);
	if(j > 0) d += p2 * (m2 / n2) * s2(left - 1, i, m1, j - 1, m2 - 1, false);
	if(left == 3) d = d / (1 - p1 * p1 * p1);
	return d;
}


ld memo1[51][51];
ld s1(int m1, int m2) {
	if(memo1[m1][m2] > -.5) return memo1[m1][m2];
	if(m1 == 0 && m2 == 0) return 0;
	ld d = 0; int i, j;
	for(i = 0; i < 3; i++)
		for(j = 0; j <= 3; j++) {
			if(i + j > 3 || (i == 0 && j == 0) || i > m1 || j > m2) continue;
			d += (1. + s1(m1 - i, m2 - j)) * s2(3, i, m1, j, m2, true);
		}
	ld ss = s2(3, 0, m1, 0, m2, true);
	d =  (d + ss) / (1. - ss);
	return memo1[m1][m2] = d;
}

int main() {
	int m1, m2, i, j, i2, i3, i4, i5;
	while(scanf("%Lf %Lf %d %d %Lf %Lf", &n1, &n2, &m1, &m2, &w1, &w2) != EOF) {
		p1 = w1 / (w1 + w2);
		p2 = w2 / (w1 + w2);
		for(i = 0; i <= m1; i++)
			for(j = 0; j <= m2; j++) {
				memo1[i][j] = -1;
				for(i2 = 0; i2 <= 3; i2++)
					for(i3 = 0; i3 <= 3; i3++)
						for(i4 = 0; i4 <= 3; i4++)
							for(i5 = 0; i5 < 2; i5++)
								memo2[i2][i3][i][i4][j][i5] = -1;

			}
		printf("%.3Lf\n", s1(m1, m2));
	}
}
