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


struct pt {
	int x, y;
	pt operator - (pt o) const { return pt{x - o.x, y - o.y}; }
	int operator ^ (pt o) const { return x * o.y - y * o.x; }
};

pt p[1123];

inline int sign(int x) { return (x > 0) - (x < 0); }

inline bool below(int l, int i, int j) {
	if(p[i].x > p[j].x) swap(i, j);
	if(p[l].x >= p[j].x || p[l].x < p[i].x) return false;
	return ((p[j] - p[i]) ^ (p[l] - p[i])) <= 0;
}

int ctR[312][312];
int ctG[312][312];

int main() {
	int tt = 0;
	int r, g, b, i, j, k, l;
	while(scanf("%d %d %d", &r, &g, &b) != EOF && r != -1) {
		for(i = 0; i < r + g + b; i++)
			scanf("%d %d", &p[i].x, &p[i].y);
		for(i = r + g; i < r + g + b; i++)
			for(j = i + 1; j < r + g + b; j++) {
				ctR[i][j] = ctG[i][j] = 0;
				for(l = 0; l < r; l++) if(below(l, i, j)) ctR[i][j]++;
				for(l = r; l < r + g; l++) if(below(l, i, j)) ctG[i][j]++;
				if(p[j].x < p[i].x) ctR[i][j] *= -1, ctG[i][j] *= -1;
				//printf("ctR[%d][%d] = %d\n", i, j, ctR[i][j]);
			}
		int RB = 0, GB = 0;
		for(i = r + g; i < r + g + b; i++)
			for(j = i + 1; j < r + g + b; j++)
				for(k = j + 1; k < r + g + b; k++) {
					int ctR = abs(::ctR[i][j] + ::ctR[j][k] - ::ctR[i][k]), ctG = abs(::ctG[i][j] + ::ctG[j][k] - ::ctG[i][k]);
					//printf("(%d, %d, %d) ctR %d ctG %d\n", i, j, k, ctR, ctG);
					if(ctR > ctG) RB++;
					else if(ctG > ctR) GB++;
				}
		printf("Case %d: %d %d\n", ++tt, RB, GB);
	}
}
