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

int di[] = {1, -1, 0,  0};
int dj[] = {0,  0, 1, -1};

struct no {
	int i, j, c, d;
	bool operator < (no o) const { return d > o.d; }
};
int r, c;
inline bool valid(int i, int j) {
	return i >= 0 && j >= 0 && i < r && j < c;
}

bitset<10009> seen[51][51];
pii nx[4][51][51];
char g[112][112];
char s[11234];

int main() {
	int i, j;
	scanf("%d %d", &r, &c);
	for(i = 0; i < r; i++)
		for(j = 0; j < c; j++)
			scanf(" %c", &g[i][j]);
	for(int d = 0; d < 4; d++)
		for(i = 0; i < r; i++)
			for(j = 0; j < c; j++) {
				int a = i, b = j;
				do {
					a = a + di[d];
					b = b + dj[d];
				} while(valid(a, b) && g[a][b] == g[i][j]);
				if(valid(a, b)) nx[d][i][j] = pii(a, b);
				else nx[d][i][j] = pii(-1, -1);
			}
	scanf("%s", s);
	s[strlen(s)] = '*';
	queue<no> pq;
	pq.push(no{0, 0, 0, 0});
	while(!pq.empty()) {
		no x = pq.front(); pq.pop();
		if(seen[x.i][x.j][x.c]) continue;
		seen[x.i][x.j][x.c] = true;
		if(s[x.c] == 0) { printf("%d\n", x.d); return 0; }
		if(g[x.i][x.j] == s[x.c]) pq.push(no{x.i, x.j, x.c + 1, x.d + 1});
		else
			for(int d = 0; d < 4; d++)
				if(nx[d][x.i][x.j].fst != -1)
					pq.push(no{nx[d][x.i][x.j].fst, nx[d][x.i][x.j].snd, x.c, x.d + 1});
	}
}
