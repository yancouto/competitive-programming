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
const ull modn = 1000000007;
inline ull mod(ull x) { return x % modn; }
#ifndef ONLINE_JUDGE
#	define debug(args...) fprintf(stderr, "%3d| ", __LINE__); fprintf(stderr, args); fprintf(stderr, "\n");
#else
#	define debug(args...)
#endif


char grid[10][30];

int convert(char c) {
	unsigned u = c;
	int value = 0;
	for(int i = 1; i <= u; i <<= 1)
		value += 250 + 250 * !!(i & u);
	return value;
}

int total(int off) {
	int tot = 0;
	for(int i = 0; i < 7; i++)
		for(int j = 0; j < 8; j++)
			if(grid[i][j + off] >= 'A' && grid[i][j + off] <= 'Z')
				tot += convert(grid[i][j + off]);
	return tot;
}

int dot_lines(int off) {
	for(int i = 0; i < 7; i++)
		for(int j = 0; j < 8; j++)
			if(grid[i][j + off] != '.')
				return i;
	return 0;
}

void shiftup(int off) {
	for(int i = 0; i < 6; i++)
		for(int j = 0; j < 8; j++)
			grid[i][j + off] = grid[i + 1][j + off];
	for(int j = 0; j < 8; j++)
		grid[6][j + off] = '.';
}

void shiftdown(int off) {
	for(int i = 6; i > 0; i--)
		for(int j = 0; j < 8; j++)
			grid[i][j + off] = grid[i - 1][j + off];
	for(int j = 0; j < 8; j++)
		grid[0][j + off] = '.';
}

int main() {
	int i;
	for_tests(t, tt) {
		printf("Case %d:\n", tt);
		for(i = 0; i < 8; i++)
			scanf(" %s", grid[i]);
		int left = dot_lines(0), right = dot_lines(10);
		int tl = total(0), tr = total(10);
		if((left == right && tl == tr) || (left < right && tr > tl) || (right < left && tl > tr))
			puts("The figure is correct.");
		else {
			for(i = 0; i < left; i++) shiftup(0);
			for(i = 0; i < right; i++) shiftup(10);
			if(tl == tr) {
				shiftdown(0);
				shiftdown(10);
			} else if(tl < tr) {
				shiftdown(10);
				shiftdown(10);
			} else {
				shiftdown(0);
				shiftdown(0);
			}
			for(i = 0; i < 7; i++)
				printf("%s\n", grid[i]);
		}

	}
	return 0;
}