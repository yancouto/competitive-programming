#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }

inline bool valid(int i, int j, int n, int m) { return i >= 0 && j >= 0 && i < n && j < m; }

vector<vector<int>> nx(const vector<vector<int>> &g) {
	int n = g.size(), m = g[0].size();
	vector<vector<int>> ng;
	ng.resize(n + 2);
	for(int i = 0; i < n + 2; i++) {
		ng[i].resize(m + 2);
		for(int j = 0; j < m + 2; j++) {
			int x = 0;
			for(int di = -2; di <= 0; di++)
				for(int dj = -2; dj <= 0; dj++)
					if(valid(i + di, j + dj, n, m))
						x ^= g[i + di][j + dj];
			ng[i][j] = x;
		}
	}
	return ng;
}

int bad;
vector<vector<int>> prev(const vector<vector<int>> &g) {
	int n = g.size(), m = g[0].size();
	vector<vector<int>> ng;
	ng.resize(n - 2);
	for(vector<int> &v : ng) v.resize(m - 2);
	for(int i = 0; i < n - 2; i++) {
		for(int j = 0; j < m - 2; j++) {
			int x = 0;
			for(int di = -2; di <= 0; di++)
				for(int dj = -2; dj <= 0; dj++)
					if((di || dj) && i + di >= 0 && j + dj >= 0)
						x ^= ng[i + di][j + dj];
			x ^= g[i][j];
			ng[i][j] = x;
		}
		for(int j = m - 2; j < m; j++) {
			int x = 0;
			for(int di = -2; di <= 0; di++)
				for(int dj = -2; dj <= 0; dj++)
					if(valid(i + di, j + dj, n - 2, m - 2))
						x ^= ng[i + di][j + dj];
			if(x != g[i][j]) {
				bad = i;
				return vector<vector<int>>();
			}
		}
	}
	for(int i = n - 2; i < n; i++) {
		for(int j = 0; j < m; j++) {
			int x = 0;
			for(int di = -2; di <= 0; di++)
				for(int dj = -2; dj <= 0; dj++)
					if(valid(i + di, j + dj, n - 2, m - 2))
						x ^= ng[i + di][j + dj];
			if(x != g[i][j]) {
				bad = i;
				return vector<vector<int>>();
			}
		}
	}
	return ng;
}

vector<vector<int>> mirror(const vector<vector<int>> &v) {
	int n = v.size(), m = v[0].size();
	vector<vector<int>> ng;
	ng.resize(m);
	for(int i = 0; i < m; i++) {
		ng[i].resize(n);
		for(int j = 0; j < n; j++)
			ng[i][j] = v[j][i];
	}
	return ng;
}

vector<vector<int>> cool_prev(vector<vector<int>> g) {
	vector<vector<int>> ng = prev(g);
	if(!ng.empty()) return ng;
	int i = bad;
	prev(mirror(g));
	int j = bad;
	//printf("swap (%d, %d)\n", i, j);
	g[i][j] ^= 1;
	ng = prev(g);
	if(!ng.empty() && nx(ng) == g) return ng;
	return vector<vector<int>>();
}

vector<vector<int>> clean(const vector<vector<int>> &g) {
	int i, j;
	int n = g.size(), m = g[0].size();
	int l = 0, r = m - 1;
	while(true) {
		int any = 0, any2 = 0;
		for(i = 0; i < n; i++)
			any += g[i][l], any2 += g[i][r];
		if(!any) l++;
		if(!any2) r--;
		if(any && any2) break;
	}
	int li = 0, ri = n - 1;
	while(true) {
		int any = 0, any2 = 0;
		for(j = 0; j < m; j++)
			any += g[li][j], any2 += g[ri][j];
		if(!any) li++;
		if(!any2) ri--;
		if(any && any2) break;
	}
	vector<vector<int>> ng;
	ng.resize(ri - li + 1);
	for(int i = li; i <= ri; i++) {
		ng[i - li].resize(r - l + 1);
		for(int j = l; j <= r; j++)
			ng[i - li][j - l] = g[i][j];
	}
	return ng;
}

int main() {
	int i, j, n, m;
	scanf("%d %d", &m, &n);
	vector<vector<int>> g;
	g.resize(n);
	for(i = 0; i < n; i++) {
		g[i].resize(m);
		for(j = 0; j < m; j++) {
			char c;
			scanf(" %c", &c);
			g[i][j] = (c == '#');
		}
	}
	g = clean(g);
	while(g.size() >= 3 && g[0].size() >= 3) {
		vector<vector<int>> ng = cool_prev(g);
		if(ng.empty()) break;
		//printf("GO BACK\n");
		g = clean(ng);
	}
	for(vector<int> &v : g) {
		for(int x : v)
			putchar(".#"[x]);
		putchar('\n');
	}
}
