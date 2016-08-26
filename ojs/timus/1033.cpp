#include <bits/stdc++.h>
using namespace std;
char g[40][40];
int dir[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
int seen[40][40][4];
int n;
struct pos {
	int i, j, d;
	pos() {}
	pos(int a, int b, int c) : i(a), j(b), d(c) {}
	bool valid() { return i >= 0 && j >= 0 && i <= n + 1 && j <= n + 1; }
};

int main() {
	int i, j;
	scanf("%d", &n);
	for(i = 1; i <= n; i++)
		for(j = 1; j <= n; j++)
			scanf(" %c", &g[i][j]);
	queue<pos> q;
	q.push(pos(1, 1, 0));
	q.push(pos(n, n, 0));
	seen[1][1][0] = 1;
	int ct = -4;
	while(!q.empty()) {
		pos p = q.front(); q.pop();
		if(g[p.i][p.j] != '.') {
			ct++;
			continue;
		}
		for(i = 0; i < 4; i++) {
			pos pp(p.i + dir[i][0], p.j + dir[i][1], i);
			if(!pp.valid()) continue;
			bool op = g[pp.i][pp.j] == '.';
			if(op && seen[pp.i][pp.j][0]) continue;
			if(!op && seen[pp.i][pp.j][pp.d]) continue;
			seen[pp.i][pp.j][op? 0 : pp.d] = 1;
			q.push(pp);
		}
	}
	printf("%d\n", ct * 9);
	return 0;
}
