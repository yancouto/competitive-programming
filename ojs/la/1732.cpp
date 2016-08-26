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

int zer, one, m, n;
char g[9][9];
pii ho[12];
int pot[11] = {1, 3, 9, 27, 81, 243, 729, 2187, 6561, 19683};
int get(int x, int i) { return (x / pot[i]) % 3; }
int add(int x, int i, int v) { return x + v * pot[i]; }

int seen[9][9], tempo;
int dx[4] = {0, 0, 1, -1};
int dy[4] = {1, -1, 0, 0};
inline bool valid(int i, int j) { return i >= 0 && j >= 0 && i < n && j < n; }
int dfs(int i, int j) {
	seen[i][j] = tempo;
	int x = 1;
	for(int k = 0; k < 4; k++) {
		int ni = i + dx[k], nj = j + dy[k];
		if(!valid(ni, nj)) continue;
		if(seen[ni][nj] == tempo || g[ni][nj] != g[i][j]) continue;
		x += dfs(ni, nj);
	}
	return x;
}

int calc(int st) {
	int i, j;
	for(i = 0; i < m; i++)
		g[ho[i].fst][ho[i].snd] = get(st, i) + '0' - 1;
	tempo++;
	int a[2] = {0, 0};
	for(i = 0; i < n; i++)
		for(j = 0; j < n; j++)
			if(seen[i][j] < tempo)
				a[g[i][j] - '0'] = max(a[g[i][j] - '0'], dfs(i, j));
	for(i = 0; i < m; i++)
		g[ho[i].fst][ho[i].snd] = '.';
	return a[1] - a[0];
}

int memo[60000][2];
int solve(int st, int turn) {
	int &r = memo[st][turn];
	if(r != -1) return r;
	int a[2] = {INT_MAX, INT_MIN};
	for(int i = 0; i < m; i++)
		if(get(st, i) == 0) {
			int x = solve(add(st, i, turn + 1), !turn);
			a[0] = min(a[0], x);
			a[1] = max(a[1], x);
		}
	if(a[0] == INT_MAX) return r = calc(st);
	return r = a[turn];
}


int main() {
	int i, j;
	while(true) {
		m = 0;
		scanf("%d", &n);
		if(!n) return 0;
		memset(seen, 0, sizeof seen); tempo = 0;
		zer = one = 0;
		for(i = 0; i < n; i++)
			for(j = 0; j < n; j++) {
				scanf(" %c", &g[i][j]);
				if(g[i][j] == '.')
					ho[m++] = pii(i, j);
				else if(g[i][j] == '1') one++;
				else zer++;
			}
		memset(memo, -1, sizeof memo);
		solve(0, zer > one);
		for(i = 0; i < m; i++)
			if(solve(add(0, i, (zer > one) + 1), !(zer > one)) == solve(0, zer > one))
				break;
		printf("(%d,%d) %d\n", ho[i].fst, ho[i].snd, ((zer > one)? 1 : -1) * solve(0, zer > one));
	}
}
