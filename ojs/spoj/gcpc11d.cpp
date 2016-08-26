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
#ifndef ONLINE_JUDGE
#	define debug(args...) fprintf(stderr, "%3d| ", __LINE__); fprintf(stderr, args); fprintf(stderr, "\n");
#else
#	define debug(args...)
#endif
const ull modn = 1000000007;
inline ull mod(ull x) { return x % modn; }
int to[5][9] = {
	{ 0,  0,  0,  0,  0,  0,  0,  0,  0},
	{ 0,  1,  0,  2,  0,  3,  0,  4,  0},
	{ 0,  0,  5,  0,  0,  0,  6,  0,  0},
	{ 0,  7,  0,  8,  0,  9,  0, 10,  0},
	{ 0,  0,  0,  0, 11,  0,  0,  0,  0}
};
int lines[6][4] = {
	{1, 2, 3, 4},
	{7, 8, 9, 10},
	{0, 2, 5, 7},
	{0, 3, 6, 10},
	{1, 5, 8, 11},
	{4, 6, 9, 11}
};
int c[12];
bool wrong_line(int i, int done) {
	if(lines[i][3] < done)
		return c[lines[i][0]] + c[lines[i][1]] + c[lines[i][2]] + c[lines[i][3]] != 22;
	return false;
}

bool check(int done) {
	for(int i = 0; i < 6; i++)
		if(wrong_line(i, done))
			return false;
	return true;
}

bool dfs(int bm, int i) {
	if(i == 12) return check(12); 
	if(c[i] != -1) return dfs(bm, i + 1);
	if(!check(i)) return false;
	for(int j = 0; j < 12; j++)
		if(!(bm & (1 << j))) {
			c[i] = j;
			if(dfs(bm | (1 << j), i + 1)) return true;
			c[i] = -1;
		}
	return false;
}

int main() {
	int i, j;
	char star[5][9];
	while(true) {
		int bm = 0;
		memset(c, -1, sizeof c);
		for(i = 0; i < 5; i++)	
			for(j = 0; j < 9; j++) {
				if(scanf(" %c", &star[i][j]) == EOF) return 0;
				if(star[i][j] != '.' && star[i][j] != 'x') {
					bm |= (1 << (star[i][j] - 'A'));
					c[to[i][j]] = star[i][j] - 'A';
				}
			}
		if(!dfs(bm, 0)) puts("ooops");
		for(i = 0; i < 5; i++) {
			for(j = 0; j < 9; j++) {
				if(star[i][j] != 'x') putchar(star[i][j]);
				else putchar(c[to[i][j]] + 'A');
			}
			putchar('\n');
		}
	}
}
