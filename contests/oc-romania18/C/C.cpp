#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define next dsadas

typedef long long ll;
typedef pair<ll,ll> pii;

const int mv[4][2] = {
	{1,0}, {0,1}, {-1,0}, {0,-1}
};
const int N =2e3+7;

int n, m;
char mat[N][N];
char res[N][N];
int which[N][N];
vector<pii> p[N*N];
pii col[N];
int ps;
int stop[N*N];
pii next[N][N];

struct evt {
	ll p, t;

	bool operator < (const evt & o) const {
		return t > o.t;
	}
};

void dfs (int i, int j, int w) {
	if (i < 0 || i >= n || j < 0 || j >= m) return;
	if (which[i][j] || mat[i][j] != '#') return;
	which[i][j] = w;
	p[w].pb(pii(i,j));
	for (int k = 0; k < 4; k++) {
		dfs(i+mv[k][0],j+mv[k][1],w);
	}
}

int main () {
	scanf("%d %d", &n, &m);
	memset(stop, -1, sizeof stop);

	for (int i = 0; i < n; i++)
		scanf(" %s", mat[i]);
	for (int i = 0; i < m; i++)
		col[i].first = -1;
	
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++) {
			res[i][j] = '.';
			if (mat[i][j] == '#' && which[i][j] == 0) {
				dfs(i,j,++ps);
			}
			if (mat[i][j] == '#') {
				next[i][j] = col[j];
				col[j] = pii(i,which[i][j]);
			}
		}

	priority_queue<evt> pq;
	for (int i = 0; i < m; i++) {
		if (col[i].first == -1) continue;
		pq.push({col[i].second,n-1-col[i].first});
	}

	while (!pq.empty()) {
		evt cur = pq.top();
		pq.pop();

		if (stop[cur.p] != -1) continue;
		stop[cur.p] = cur.t;
		//cout << cur.p << " " << cur.t << endl;

		for (pii g : p[cur.p]) {
			if (next[g.first][g.second].first == -1) continue;
			pq.push({next[g.first][g.second].second,cur.t + abs(g.first-next[g.first][g.second].first) - 1});
		}
	}

	for (int i = 1; i <= ps; i++)
		for (pii g : p[i])
			res[g.first+stop[i]][g.second] = '#';
	for (int i = 0; i < n; i++)
		printf("%s\n", res[i]);
}
