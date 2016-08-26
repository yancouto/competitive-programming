#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef unsigned long long ull;
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
template<typename T> inline T abs(T t) { return t < 0? -t : t; }
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }
const int N = 2003;

void err() { puts("ERROR"); exit(0); }

int di[8] = {-1, 1, 0, 1, 1,-1, 0,-1};
int dj[8] = { 0, 1, 1,-1, 0,-1,-1, 1};
int n, m;
inline bool valid(int i, int j) { return i >= 0 && j >= 0 && i < n && j < n; }
inline int op(int d) { return (d + 4) % 8; }
int memo[N][N][8];
char g[N][N]; bool mrk[N][N];
int eq(int i, int j, int d) {
	if(!valid(i, j) || g[i][j] == '.') return 0;
	if(memo[i][j][d] != -1) return memo[i][j][d];
	if(valid(i + di[d], j + dj[d]) && g[i][j] == g[i+di[d]][j+dj[d]])
		return memo[i][j][d] = 1 + eq(i + di[d], j + dj[d], d);
	else return memo[i][j][d] = 1;
}
bool win[2] = {false, false};
bool more = false;
bool wp[N][N];

void visit(int i, int j) {
	mrk[i][j] = true;
	for(int d = 0; d < 8; d++) {
		int ni = i + di[d], nj = j + dj[d];
		if(valid(ni, nj) && !mrk[ni][nj] && g[i][j] == g[ni][nj] && wp[ni][nj])
			visit(ni, nj);
	}
}

void anal() {
	int i, j, d;
	for(i = 0; i < n; i++)
		for(j = 0; j < n; j++)
			for(d = 0; d < 4; d++)
				if(eq(i, j, d) + eq(i, j, d + 4) - 1 >= m)
					wp[i][j] = true;
	for(i = 0; i < n; i++)
		for(j = 0; j < n; j++) {
			if(g[i][j] == '.') continue;
			int wins = 0;
			for(d = 0; d < 4; d++) {
				int v = eq(i, j, d) + eq(i, j, d + 4) - 1;
				if(v > 2 * m - 1) err();
				wins += (v >= m);
			}
			if(!wins) continue;
			bool x = g[i][j] == 'X';
			if(win[!x] || (win[x] && !mrk[i][j]) || (wins > 1 && more)) err();
			if(!win[x]) visit(i, j), win[x] = true;
			if(wins == 1) continue;
			more = true;
			for(d = 0; d < 8; d++)
				if(eq(i, j, d) - 1 >= m)
					err();
		}
}

int main() {
	memset(memo, -1, sizeof memo);
	int i, j, nX = 0, nO = 0;
	scanf("%d %d", &n, &m);
	for(i = 0; i < n; i++)
		for(j = 0; j < n; j++) {
			scanf(" %c", &g[i][j]);
			nX += (g[i][j] == 'X');
			nO += (g[i][j] == 'O');
		}
	if(nX > nO + 1) err();
	anal();
	if(win[1]) {
		if(nO != nX - 1) err();
		puts("X WINS");
	} else if(win[0]) {
		if(nO != nX) err();
		puts("O WINS");
	} else if(nX + nO != n*n)
		puts("IN PROGRESS");
	else puts("DRAW");
}
