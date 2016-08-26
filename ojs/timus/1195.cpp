#include <bits/stdc++.h>
using namespace std;

char g[3][3];
bool win_X(char c='X') {
	if(g[0][0] == g[1][1] && g[1][1] == g[2][2] && g[0][0] == c) return true;
	if(g[0][2] == g[1][1] && g[1][1] == g[2][0] && g[1][1] == c) return true;
	int i, j;
	for(i = 0; i < 3; i++) {
		bool all = true;
		for(j = 0; j < 3; j++)
			if(g[i][j] != c)
				all = false;
		if(all) return true;
		all = true;
		for(j = 0; j < 3; j++)
			if(g[j][i] != c)
				all = false;
		if(all) return true;
	}
	return false;
}
bool win_O() { win_X('O'); }

int solve(bool x, int left) {
	if(left == 0) return 2;
	int i, j;
	char c = x? 'X' : 'O';
	bool win = false, draw = false;
	for(i = 0; i < 3; i++)
		for(j = 0; j < 3; j++) {
			if(g[i][j] != '#') continue;
			g[i][j] = c;
			if(win_X(c)) win = true;
			int k = solve(!x, left - 1);
			if(k == x) win = true;
			if(k == 2) draw = true;
			g[i][j] = '#';
		}
	if(win) return x;
	if(draw) return 2;
	return !x;
}

int main() {
	int i, j;
	for(i = 0; i < 3; i++)
		for(j = 0; j < 3; j++)
			scanf(" %c", &g[i][j]);
	int k = solve(true, 3);
	if(k == 0) puts("Ouths win");
	else if(k == 1) puts("Crosses win");
	else puts("Draw");
}
