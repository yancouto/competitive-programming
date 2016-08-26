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
int fl[256], n, m;
char grid[102][102];

int seen[102][102], tempo;
int dir[4][2] = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};
bool valid(int i, int j) { return i >= 0 && j >= 0 && i < n && j < m; }
bool walk() {
	if(grid[0][0] == '.') return false;
	tempo++;
	int i = 0, j = 0, d;
	while(valid(i, j)) {
		if(seen[i][j] == tempo) return false;
		seen[i][j] = tempo;
		if(grid[i][j] == '*') return true;
		if(grid[i][j] != '.') d = fl[grid[i][j]];
		i += dir[d][0]; j += dir[d][1];
	}
	return false;
}

int main() {
	int i, j;
	fl['^'] = 0;
	fl['v'] = 1;
	fl['>'] = 2;
	fl['<'] = 3;
	while(scanf("%d %d", &m, &n) != EOF) {
		for(i = 0; i < n; i++)
			for(j = 0; j < m; j++)
				scanf(" %c", &grid[i][j]);
		printf("%c\n", walk()? '*' : '!');
	}
	return 0;
}
