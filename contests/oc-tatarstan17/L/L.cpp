#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll,ll> pii;

const int N = 5e3+7;

int n, m;
char mat[N][N];
int uf[N], wf[N], vl[N];

int find (int u) {
	if (u == uf[u]) return u;
	return uf[u] = find(uf[u]);
}

void join (int u, int v) {
	if ((u = find(u)) == (v = find(v))) {
		vl[u]++;
		return;
	}
	if (wf[u] < wf[v]) swap(u,v);
	wf[u] += wf[v];
	uf[v] = u;
	vl[u] += vl[v] + 1;
}

int main () {
	scanf("%d %d", &n, &m);

	for (int i = 0; i < n+m; i++) {
		uf[i] = i;
		wf[i] = 1;
		vl[i] = 0;
	}

	int cc = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			char c;
			scanf(" %c", &c);
			mat[i][j] = c;
			if (c == '.') {
				cc++;
			} else {
				join(i, j+n);
			}
		}
	}

	if (cc == 0 || cc == n*m) {
		printf("0\n");
		return 0;
	}
	
	int mx = 0;
	pii rs(0,0);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (mat[i][j] == '+') continue;
			int u = find(i);
			int v = find(j+n);
			int loc = 0;
			loc += vl[v];
			if (u != v)
				loc += vl[u];
			if (loc >= mx) {
				mx = loc;
				rs = pii(i,j);
			}
		}
	}

	printf("%d\n", mx);
	printf("%d %d\n", rs.first+1, rs.second+1);
}
