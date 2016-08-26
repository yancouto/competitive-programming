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
char g[30][30];
int ci, cj, bi, bj, si, sj;
int n, m;

struct no {
	int i, j, bi, bj, bm, dist;
	no() {}
	no(int a, int b, int c, int d, int e, int f) : i(a), j(b), bi(c), bj(d), bm(e), dist(f) {}
	bool operator < (const no &o) const {
		int a1 = __builtin_popcount(bm), a2 = __builtin_popcount(o.bm);
		bool sm;
		if(a1 == a2) sm = dist < o.dist;
		else sm = a1 < a2;
		return !sm;
	}
};

int seen[26][26][26][26][32], tempo;
int dir[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
inline bool valid(int i, int j) { return i >= 0 && j >= 0 && i < n && j < m; }
pii solve() {
	priority_queue<no> pq;
	tempo++;
	pq.push(no(ci, cj, bi, bj, 0, 0));
	while(!pq.empty()) {
		no x = pq.top();
		pq.pop();
		if(seen[x.i][x.j][x.bi][x.bj][x.bm] == tempo) continue;
		seen[x.i][x.j][x.bi][x.bj][x.bm] = tempo;
		if(x.bi == si && x.bj == sj) return pii(__builtin_popcount(x.bm), x.dist);
		for(int d = 0; d < 4; d++) {
			int ni = x.i + dir[d][0], nj = x.j + dir[d][1], nbi = x.bi, nbj = x.bj, nbm = x.bm;
			if(!valid(ni, nj)) continue;
			char c = g[ni][nj];
			if(c == '*') continue;
			if(ni == x.bi && nj == x.bj) {
				nbi += dir[d][0];
				nbj += dir[d][1];
				if(!valid(nbi, nbj)) continue;
				char c2 = g[nbi][nbj];
				if(c2 == '*' || (c2 < 10 && !(nbm & (1 << c2)))) continue;
			}
			if(c < 10) nbm |= (1 << c);
			pq.push(no(ni, nj, nbi, nbj, nbm, x.dist + 1));
		}
	}
	return pii(-1, -1);
}

int main() {
	int i, j;
	while(scanf("%d %d", &n, &m) != EOF) {
		int ps = 0;
		for(i = 0; i < n; i++)
			for(j = 0; j < m; j++) {
				scanf(" %c", &g[i][j]);
				if(g[i][j] == 'j') {
					g[i][j] = '.';
					ci = i; cj = j;
				}
				if(g[i][j] == 'b') {
					g[i][j] = '.';
					bi = i; bj = j;
				}
				if(g[i][j] == 'x') {
					g[i][j] = '.';
					si = i; sj = j;
				}
				if(g[i][j] == '#')
					g[i][j] = (ps++);
				
			}
		pii p = solve();
		if(p.fst == -1) puts("-1");
		else printf("%d %d\n", p.fst, p.snd);
	}
}
