#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll,ll> pii;
#define pb push_back

int n, m;
inline int id(int i, int j) { return i * m + j; }

const int N = 212345;

int en = 2;
int tempo;

int seen[N], fl[N], nx[N], he[N], to[N];


bool dfs(int s, int t) {
	if(s == t) return true;
	if(seen[s] == tempo) return false;
	seen[s] = tempo;
	for(int e = he[s]; e; e = nx[e])
		if((e & 1) - fl[e] && dfs(to[e], t)) {
			fl[e]++;
			fl[e ^ 1]--;
			return true;
		}
	return false;
}

int max_flow(int s, int t) {
	int f = 0; tempo++;
	while(dfs(s, t))
		f++, tempo++;
	return f;
}

void add_edge(int a, int b) {
	nx[en] = he[b]; to[en] = a; he[b] = en++;
	nx[en] = he[a]; to[en] = b; he[a] = en++;
}

char g[112][112];
int S[N], sz[N];
int find(int i) {
	if(S[S[i]] != S[i]) S[i] = find(S[i]);
	return S[i];
}

inline void join(int a, int b) {
	if((a = find(a)) == (b = find(b))) return;
	if(sz[a] < sz[b]) swap(a, b);
	sz[a] += sz[b];
	S[b] = a;
}

int di[] = {1, -1, 0,  0};
int dj[] = {0,  0, 1, -1};

int main () {
	int i, j, d;
	scanf("%d %d", &n, &m);
	for(i = 0; i < n; i++)
		for(j = 0; j < m; j++)
			scanf(" %c", &g[i][j]);
	for(i = 0; i < n * m; i++) S[i] = i, sz[i] = 1;
	for(i = 0; i < n; i++)
		for(j = 0; j < m; j++) {
			if(g[i][j] != 'L') continue;
			//printf("[%d][%d] %d\n", i, j, id(i, j));
			for(d = 0; d < 4; d++) {
				int ni = i + di[d];
				int nj = j + dj[d];
				if(ni < 0 || nj < 0 || ni >= n || nj >= m) continue;
				if(g[ni][nj] == 'L') join(id(i, j), id(ni, nj));
				//if(g[ni][nj] == 'L') printf("(%d, %d) join (%d, %d)\n", i, j, ni, nj);
				if(g[ni][nj] == 'C') g[ni][nj] = 'W';
			}
			//printf("[%d][%d] %d\n", i, j, find(id(i, j)));
		}
	int ct = 0;
	for(i = 0; i < n * m; i++) ct += (g[i / m][i % m] == 'L' && (find(i) == i));
	int all = 0;
	for(i = 0; i < n; i++)
		for(j = 0; j < m; j++) {
			if(g[i][j] != 'C') continue;
			all++;
			if((i + j) & 1) {
				add_edge(n * m, id(i, j));
			} else {
				add_edge(id(i, j), n * m + 1);
				continue;
			}
			for(d = 0; d < 4; d++) {
				int ni = i + di[d];
				int nj = j + dj[d];
				if(ni < 0 || nj < 0 || ni >= n || nj >= m) continue;
				if(g[ni][nj] == 'C') add_edge(id(i, j), id(ni, nj));
			}
		}
	printf("%d\n", ct + (all - max_flow(n * m, n * m + 1)));
}
