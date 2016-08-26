#include <cstdio>
#include <cstring>
#include <algorithm>
typedef std::pair<int, int> point;
#define x first
#define y second
inline int abs(int x) { return x < 0? -x : x; }

int grid[13][13];
// 0 - obstaculo
// 1 - vazio
bool seen[7][7][7][7][7][7][7][7];

bool confl(point ps[4], point p) {
	for(int i = 0; i < 4; i++)
		if(p.x != ps[i].x || p.y != ps[i].y) {
			if(abs(ps[i].x - p.x) <= 1 && abs(ps[i].y - p.y) <= 1)
				return true;
		}
	for(int i = 0; i < 2; i++)
		for(int j = 0; j < 2; j++)
			if(grid[p.x + i][p.y + j] == 0)
				return true;
	return false;
}
void move(point ps[4], point to[4], int dir[2]) {
	bool block; int i; point bak;
	for(i = 0; i < 4; i++) to[i] = ps[i];
	do {
		block = true;
		for(i = 0; i < 4; i++) {
			bak = to[i];
			to[i].x += dir[0];
			to[i].y += dir[1];
			if(confl(to, to[i]))
				to[i] = bak;
			else
				block = false;
		}
	} while(!block);
}
bool first;
int dirs[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
int dfs(point ps[4]) {
	bool &b = seen[ps[0].x - 1][ps[0].y - 1][ps[1].x - 1][ps[1].y - 1][ps[2].x - 1][ps[2].y - 1][ps[3].x - 1][ps[3].y - 1];
	if(b) return 0;
	int tot = 1;
	if(first) {
		tot = 0;
		first = false;
	}
	else
		b = true;
	point o[4];
	for(int i = 0; i < 4; i++) {
		move(ps, o, dirs[i]);
		tot += dfs(o);
	}
	return tot;
}

int main() {
	int t, i, j; char c;
	scanf("%d", &t);
	point p[4];
	for(int tt = 1; tt <= t; tt++) {
		for(i = 0; i < 4; i++) p[i].x = -1;
		for(i = 1; i <= 8; i++)
			for(j = 1; j <= 8; j++) {
				scanf(" %c", &c);
				if(c == '.') grid[i][j] = 1;
				else if(c == '#') grid[i][j] = 0;
				else {
					grid[i][j] = 1;
					if(p[c - 'A'].x == -1)
						p[c - 'A'] = point(i, j);	
				}
			}
		memset(seen, 0, sizeof seen);
		first = true;
		printf("Case %d: %d\n", tt, dfs(p));
	}
	return 0;
}