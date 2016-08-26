#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
template<typename T> inline T abs(T t) { return t < 0? -t : t; }
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, unsigned> pii;

int g[4][4];
ull hsh() {
	ull h = 0;
	for(int i = 0; i < 4; i++)
		for(int j = 0; j < 4; j++)
			h |= ull(g[i][j]) << ((i * 4 + j) * 4);
	return h;
}

bool ok(int i, int j) {
	if(i != 3 || j != 3) return false;
	for(i = 0; i < 4; i++)
		for(j = 0; j < 4; j++)
			if(g[i][j] != i * 4 + j + 1)
				return false;
	return true;
}

bool cut(int i, int j, int moves_left) {
	if((3 - i) + (3 - j) > moves_left) return true;
	int sum = 0;
	for(i = 0; i < 4; i++)
		for(j = 0; j < 4; j++)
			if(g[i][j])
				sum += abs((g[i][j] - 1) / 4 - i) + abs(((g[i][j] - 1) % 4) - j);
	return sum > moves_left;
}

inline bool valid(int i, int j) { return i >= 0 && j >= 0 && i < 4 && j < 4; }

const int mx = 46;
int dx[4] = {1, -1, 0, 0};
int dy[4] = {0, 0, 1, -1};
unordered_map<ull, int> seen;
char act[53]; int an;
bool solve(int i, int j) {
	if(ok(i, j)) {
		act[an] = 0;
		puts(act);
		return true;
	}
	g[i][j] = 0;
	if(an > mx) return false;
	if(cut(i, j, mx - an)) return false;

	ull h = hsh();
	if(seen.count(h) && seen[h] <= an) return false;
	seen[h] = an;
	for(int d = 0; d < 4; d++) {
		int ni = i + dx[d], nj = j + dy[d];
		if(!valid(ni, nj)) continue;
		act[an++] = "DURL"[d];
		swap(g[i][j], g[ni][nj]);
		if(solve(ni, nj)) return true;
		swap(g[i][j], g[ni][nj]);
		an--;
	}
	return false;
}

int si, sj;
bool pos() {
	g[si][sj] = 16;
	int p[17] = {-1}, i, j;
	for(i = 0; i < 4; i++)
		for(j = 0; j < 4; j++)
			p[g[i][j]] = i * 4 + j;
	for(i = 1; i <= 16; i++)
		if(p[i] == -1)
			return false;
	int pa = 0;
	for(i = 1; i <= 16; i++)
		for(j = i + 1; j <= 16; j++)
			if(p[j] < p[i])
				pa = !pa;
	g[si][sj] = 0;
	return pa == (((3 - si) + (3 - sj)) & 1);
}

int main() {
	int t, i, j;
	scanf("%d", &t);
	while(t--) {
		si = sj = -1;
		for(i = 0; i < 4; i++)
			for(j = 0; j < 4; j++) {
				scanf("%d", &g[i][j]);
				if(!g[i][j]) si = i, sj = j;
			}
		if(si == -1 || !pos()) { puts("This puzzle is not solvable."); continue; }
		if(si == 3 && sj == 3 && ok(si, sj)) { puts("UD"); continue; }
		g[si][sj] = 0;
		seen.clear();
		an = 0;
		seen.clear();
		if(!solve(si, sj))
			puts("This puzzle is not solvable.");
	}
}
