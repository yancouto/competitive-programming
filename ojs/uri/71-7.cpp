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

inline bool valid(int i, int j) { return i >= 0 && j >= 0 && i <= 20 && j <= 20; }

int dx[4] = {1, -1, 0, 0};
int dy[4] = {0, 0, 1, -1};
int memo[22][22][1003];
int tr[22][22][1003];
int solve(int i, int j, int t) {
	if(t > 1000) return 0;
	int &r = memo[i][j][t];
	if(r != -1) return r;
	r = solve(i, j, t + 1);
	for(int d = 0; d < 4; d++) {
		int ni = i + dx[d], nj = j + dy[d];
		if(!valid(ni, nj)) continue;
		r = max(r, solve(ni, nj, t + 1));
	}
	r += tr[i][j][t];
	return r;
}

int main() {
	int i, n, x, y, t;
	scanf("%d", &n);
	for(i = 0; i < n; i++) {
		scanf("%d %d %d", &x, &y, &t);
		tr[x][y][t]++;
	}
	memset(memo, -1, sizeof memo);
	printf("%d\n", solve(6, 6, 0));
}
