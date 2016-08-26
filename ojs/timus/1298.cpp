#include <bits/stdc++.h>
using namespace std;
int n;
int g[9][9];
void deb(int i, int j) { printf("%c%d\n", i + 'a', j + 1); }
int dx[8] = {1, 2, 2, 1, -1, -2, -2, -1};
int dy[8] = {-2, -1, 1, 2, 2, 1, -1, -2};
inline bool valid(int i, int j) { return i >= 0 && j >= 0 && i < n && j < n && !g[i][j]; }
bool solve(int i, int j, int mv) {
	if(mv == n * n) { deb(i, j); return true; }
	g[i][j] = true;
	for(int k = 0; k < 8; k++)
		if(valid(i + dx[k], j + dy[k]) && solve(i + dx[k], j + dy[k], mv + 1)) {
			deb(i, j);
			return true;
		}
	g[i][j] = false;
	return false;
}
int x[10], y[10];
int main() {
	int i, j;
	scanf("%d", &n);
	for(i = 0; i < n; i++)
		for(j = 0; j < n; j++)
			if(solve(i, j, 1))
				return 0;
	puts("IMPOSSIBLE");
}
