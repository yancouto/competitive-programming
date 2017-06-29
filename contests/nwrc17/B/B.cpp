#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll,ll> pii;

const int N = 55;

char mv[4][2] = {
	{0,-1},
	{-1,0},
	{0,1},
	{1,0}
};

struct node {
	int i, j, k;

	node (int a, int b, int c) : i(a), j(b), k(c) {}
};

char mat[N][N];
int n, m;
char str[N];

int dist[N][N][N];
int visi[N][N][N];
deque<node> qu;

int rel (char c) {
	if (c == 'L')
		return 0;
	if (c == 'U')
		return 1;
	if (c == 'R')
		return 2;
	if (c == 'D')
		return 3;
	return 4;
}

int main () {
	memset(dist, -1, sizeof dist);
	cin >> n >> m;

	for (int i = 0; i < n; i++)
		cin >> mat[i];
	
	cin >> str;

	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++) {
			if (mat[i][j] == 'R') {
				dist[i][j][0] = 0;
				qu.push_back(node(i,j,0));
			}
		}

	while (!qu.empty()) {
		node u = qu.front();	
		qu.pop_front();

		//cout << u.i << " " << u.j << " " << u.k << ": " << dist[u.i][u.j][u.k] << endl;

		if (mat[u.i][u.j] == 'E') {
			cout << dist[u.i][u.j][u.k] << endl;
			return 0;
		}

		if (visi[u.i][u.j][u.k]) continue;
		visi[u.i][u.j][u.k] = 1;

		for (int l = 0; l < 6; l++) {
			node v = u;
			ll ds = dist[u.i][u.j][u.k];
			bool ty = 0;
			if (l < 4) {
				v.i += mv[l][0];
				v.j += mv[l][1];
				ds++;
				ty = 1;
			} else if (l == 4) {
				if (!str[u.k]) continue;
				v.i += mv[rel(str[u.k])][0];
				v.j += mv[rel(str[u.k])][1];

				if (v.i < 0 || v.i >= n || v.j < 0 || v.j >= m || mat[v.i][v.j] == '#') {
					v.i = u.i; v.j = u.j;
				}

				v.k++;
			} else if (l == 5) {
				if (!str[u.k]) continue;
				v.k++;
				ds++;
				ty = 1;
			}

			if (v.i < 0 || v.i >= n || v.j < 0 || v.j >= m) continue;
			if (mat[v.i][v.j] == '#') continue;
			
			if (dist[v.i][v.j][v.k] == -1 || ds < dist[v.i][v.j][v.k]) {
				dist[v.i][v.j][v.k] = ds;
				if (ty)
					qu.push_back(v);
				else
					qu.push_front(v);
			}
		}
	}
}
