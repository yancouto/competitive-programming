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
inline int count_1s(int x) { return __builtin_popcount(x); }
inline int count_1s(ull x) { return __builtin_popcountll(x); }
template<typename T> inline T abs(T t) { return t < 0? -t : t; }
const ull modn = 1000000007;
inline ull mod(ull x) { return x % modn; }
#ifndef ONLINE_JUDGE
#	define debug(args...) fprintf(stderr, "%3d| ", __LINE__); fprintf(stderr, args); fprintf(stderr, "\n");
#else
#	define debug(args...)
#endif
int w, h;
char g[1504][1504];
struct pos { int x, y; };
int ds[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
int seen[3][1504][1504];

inline char at(pos p) { return g[p.x][p.y]; }
inline pos trans(pos p, int d) { return {p.x + ds[d][0], p.y + ds[d][1]}; }
int side;
void hand(int i, pos p, int look) {
	seen[i][p.x][p.y] = 1;
	if(p.x == h && p.y == w) return;
	int r = (look + side + 4) % 4;
	if(at(trans(p, r)) == '.') hand(i, trans(p, r), r);
	else if(at(trans(p, look)) == '.') hand(i, trans(p, look), look);
	else hand(i, p, (look - side + 4) % 4);
}

void acc() {
	int i, j, k;

	for(i = 0; i <= h + 1; i++)
		for(j = 1; j <= w + 1; j++)
			for(k = 0; k < 3; k++)
				seen[k][i][j] += seen[k][i][j - 1];
	for(i = 1; i <= h + 1; i++)
		for(j = 0; j <= w + 1; j++)
			for(k = 0; k < 3; k++)
				seen[k][i][j] += seen[k][i - 1][j];
}

int get(int k, int x1, int y1, int x2, int y2) {
	return seen[k][x2][y2] - seen[k][x2][y1 - 1] - seen[k][x1 - 1][y2] + seen[k][x1 - 1][y1 - 1];
}

inline bool valid(int i, int j) {
	return i <= h && j <= w;
}

bool poss(int i, int j, int m) {
	if(!valid(i + m - 1, j + m - 1)) return true;
	return (get(1, i, j, i + m - 1, j + m - 1) > 0) && (get(2, i, j, i + m - 1, j + m - 1) > 0);
}

bool poss2(int i, int j, int m) {
	return get(0, i, j, i + m - 1, j + m - 1) == 0;
}

int main() {
	int i, j;
	while(scanf("%d %d", &w, &h) != EOF) {
		for(i = 1; i <= h; i++) {
			for(j = 1; j <= w; j++)
				scanf(" %c", &g[i][j]);
			g[i][0] = g[i][w + 1] = '#';
		}
		for(i = 0; i <= w + 1; i++)
			g[0][i] = g[h + 1][i] = '#';
		for(i = 0; i <= h + 1; i++) {
			for(j = 0; j <= w + 1; j++) {
				seen[0][i][j] = (g[i][j] == '#');
				seen[1][i][j] = seen[2][i][j] = 0;
			}
		}
		seen[0][1][1] = seen[0][h][w] = 1;
		side = 1; //direita
		hand(1, {1, 1}, 1);
		side = -1;
		hand(2, {1, 1}, 1);
		acc();
		int mir = INT_MAX;
		pos mi;
		for(i = 1; i <= h; i++)
			for(j = 1; j <= w; j++) {
				int l = 1, r = max(h, w);
				while(l < r) {
					int m = (l + r) / 2;
					if(poss(i, j, m)) r = m;
					else l = m + 1;
				}
				if(poss2(i, j, l) && l < mir) {
					mir = l;
					mi = {i, j};
				}
			}
		if(mir == INT_MAX) puts("Impossible");
		else printf("%d %d %d\n", mir, mi.y, mi.x);
	}
}