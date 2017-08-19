#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> pii;

const int N = 20;
int A[1 << 15][N][N];

int ki[] = {2,  2, -2, -2, 1, -1,  1, -1};
int kj[] = {1, -1,  1, -1, 2,  2, -2, -2};

int bi[] = {1,  1, -1, -1};
int bj[] = {1, -1,  1, -1};

int ri[] = {1, -1, 0,  0};
int rj[] = {0,  0, 1, -1};

char g[N][N];

int ene[N][N];
int n, m;

bool go(int A[N][N], int i, int j, int bm, int di, int dj) {
	i += di;
	j += dj;
	if(i < 0 || i >= n || j < 0 || j >= m) return false;
	if(g[i][j] != '.' && ((bm >> ene[i][j]) & 1)) return false;
	A[i][j]++;
	return true;
}

void mrk(int A[N][N], int bm, int i, int j) {
	if(g[i][j] == 'K') {
		for(int d = 0; d < 8; d++)
			go(A, i, j, bm, ki[d], kj[d]);
	} else if(g[i][j] == 'B') {
		for(int d = 0; d < 4; d++)
			for(int k = 1; go(A, i, j, bm, bi[d] * k, bj[d] * k); k++);
	} else {
		for(int d = 0; d < 4; d++)
			for(int k = 1; go(A, i, j, bm, ri[d] * k, rj[d] * k); k++);
	}
}

int en;


struct no {
	int i, j, bm;
	int d;
	bool operator < (no o) const {
		if(i != o.i) return i < o.i;
		if(j != o.j) return j < o.j;
		return bm < o.bm;
	}
};
int seen[15][15][1 << 15];

int di[] = {1,  1, -1, -1, 1, -1, 0,  0};
int dj[] = {1, -1,  1, -1, 0,  0, 1, -1};


int main() {
#ifdef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	scanf("%d %d", &n, &m);
	int i, j;
	int si, sj;
	for(i = 0; i < n; i++)
		for(j = 0; j < m; j++) {
			scanf(" %c", &g[i][j]);
			if(g[i][j] == '*') si = i, sj = j, g[i][j] = '.';
			if(g[i][j] != '.') ene[i][j] = en;
			if(g[i][j] != '.') en++;
		}
	//printf("en %d\n", en);
	for(int bm = 0; bm < (1 << en); bm++) {
		for(i = 0; i < n; i++)
			for(j = 0; j < m; j++) {
				if(g[i][j] != '.' && !((bm >> ene[i][j]) & 1)) continue;
				if(g[i][j] != '.') mrk(A[bm], bm, i, j);
			}
	}
	//for(i = 0; i < n; i++)
	//	for(j = 0; j < m; j++)
	//		printf("%2d%c", A[(1 << en) - 1][i][j], " \n"[j == m - 1]);
	queue<no> q;
	q.push(no{si, sj, (1 << en) - 1, 0});
	seen[si][sj][(1 << en) - 1] = 1;
	while(!q.empty()) {
		no x = q.front(); q.pop();
		if(x.bm == 0) {
			printf("%d\n", x.d);
			//while(true) {
			//	printf("x (%d, %d) bm %d d %d\n", x.i, x.j, x.bm, x.d);
			//	if(!p.count(x)) break;
			//	x = p[x];
			//}
			return 0;
		}
		for(int d = 0; d < 8; d++) {
			no y = x;
			y.i += di[d];
			y.j += dj[d];
			if(y.i < 0 || y.i >= n || y.j < 0 || y.j >= m) continue;
			if(g[y.i][y.j] != '.' && ((y.bm >> ene[y.i][y.j]) & 1)) y.bm ^= (1 << ene[y.i][y.j]);
			if(A[y.bm][y.i][y.j] > 0) continue;
			if(seen[y.i][y.j][y.bm]) continue;
			seen[y.i][y.j][y.bm] = 1;
			y.d++;
			//printf("x (%d, %d) bm %d d %d\n", x.i, x.j, x.bm, x.d);
			//printf("y (%d, %d) bm %d d %d\n\n", y.i, y.j, y.bm, y.d);
			q.push(y);
		}
	}
	puts("-1");
}
