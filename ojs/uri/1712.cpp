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
int g[52][52], n, m;
int mx;
int dir[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
bool valid(int i, int j) { return i >= 0 && j >= 0 && i < n && j < n; }

ull get_hash(vector<pii> &v) {
	ull h = 0;
	for(pii p : v)
		h = h * 463llu + 20llu * (p.fst + 10llu) + p.snd + 10llu;
	return h;
}
vector<vector<pii> > pcs;
set<ull> seen;
int dx[4] = {1, -1, 0, 0};
int dy[4] = {0, 0, 1, -1};
void gen(vector<pii> &v) {
	pii g(v[0]);
	if(g != pii(0, 0))
		for(pii &p : v)
			p.fst -= g.fst,
			p.snd -= g.snd;
	if(!seen.insert(get_hash(v)).snd) return;
	if(v.size() == m) { pcs.pb(v); return; }
	for(pii p : v) {
		for(int d = 0; d < 4; d++) {
			pii h(p.fst + dx[d], p.snd + dy[d]);
			if(binary_search(v.begin(), v.end(), h)) continue;
			vector<pii> v2(v);
			v2.pb(h);
			int j = v2.size() - 1;
			while(j && v2[j] < v2[j-1]) { swap(v2[j], v2[j-1]); j--; }
			gen(v2);
		}
	}
}

int sum(int i, int j, vector<pii> &pc) {
	int s = 0;
	for(pii p : pc) {
		if(!valid(p.fst + i, p.snd + j)) return -1;
		s += g[p.fst + i][p.snd + j];
	}
	return s;
}

int main() {
	vector<pii> v; v.pb(pii(0, 0));
	scanf("%d %d", &n, &m);
	gen(v);
	int i, j;
	for(i = 0; i < n; i++)
		for(j = 0; j < n; j++)
			scanf("%d", &g[i][j]);
	int mx = 0;
	for(vector<pii> &v : pcs)
		for(i = 0; i < n; i++)
			for(j = 0; j < n; j++)
				mx = max(mx, sum(i, j, v));
	printf("%d\n", mx);
	return 0;
}
