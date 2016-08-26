#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;
const double circ = M_PI / 4.;
const double other = 4. - 2 * circ;
typedef pair<int, int> pii;
int r, c, e;
char grid[103][103];
pii es[40009][2];

void add(int x1, int y1, int x2, int y2) {
	es[e][0] = make_pair(x1, y1);
	es[e++][1] = make_pair(x2, y2);
}
inline int s1(int x) { return x << 1; }
inline int s2(int x) { return s1(x) + 1; }
inline int s3(int x) { return s1(x) + 2; }
#define f first
#define s second
pii S[204][204];
int size[204][204];
double g[204][204];
pii find(pii p) {
	if(S[S[p.f][p.s].f][S[p.f][p.s].s] != S[p.f][p.s])
		S[p.f][p.s] = find(S[p.f][p.s]);
	return S[p.f][p.s];
}

void join(pii a, pii b) {
	if(a == b) return;
	if(size[a.f][a.s] < size[b.f][b.s]) swap(a, b);
	size[a.f][a.s] += size[b.f][b.s];
	g[a.f][a.s] += g[b.f][b.s];
	S[b.f][b.s] = a;
}


int main() {
	int t, i, j, x, y;
	scanf("%d", &t);
	for(int tt = 1; tt <= t; tt++) {
		scanf("%d %d", &r, &c);
		for(i = 0; i < r; i++)
			scanf(" %s", grid[i]);
		for(i = 0; i < r; i++)
			for(j = 0; j < c; j++) {
				for(x = s1(i); x <= s3(i); x++)
					for(y = s1(j); y <= s3(j); y++) {
						g[x][y] = 0; size[x][y] = 1;
						S[x][y] = make_pair(x, y);
					}
			}
		e = 0;
		for(i = 0; i < r; i++)
			for(j = 0; j < c; j++) {
				if(grid[i][j] == '0') {
					g[s1(i)][s1(j)] += circ;
					g[s3(i)][s3(j)] += circ;
					g[s2(i)][s2(j)] += other;
					add(s2(i), s2(j), s3(i), s1(j));
					add(s2(i), s2(j), s1(i), s3(j));
				} else {
					g[s3(i)][s1(j)] += circ;
					g[s1(i)][s3(j)] += circ;
					g[s2(i)][s2(j)] += other;
					add(s2(i), s2(j), s1(i), s1(j));
					add(s2(i), s2(j), s3(i), s3(j));
				}
			}
		for(i = 0; i < e; i++)
			join(find(es[i][0]), find(es[i][1]));
		int q;
		scanf("%d", &q);
		printf("Case %d:\n", tt);
		for(i = 0; i < q; i++) {
			scanf("%d %d", &x, &y);
			pii p = find(make_pair(x, y));
			printf("%.4f\n", g[p.f][p.s]);
		}

	}
	return 0;
}