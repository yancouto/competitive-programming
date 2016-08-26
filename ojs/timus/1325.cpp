#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef pair<int, int> pii;

struct no {
	int i, j;
	pii d;
	bool operator < (no o) const { return d > o.d; }
	no() {}
	no(int a, int b, int c, int dd) : i(a), j(b), d(c, dd) {}
};
int seen[502][502];
int dx[8] = {1, -1, 0, 0, 1, -1, -1, 1};
int dy[8] = {0, 0, 1, -1, 1, -1, 1, -1};
int n, m;
char g[502][502];
inline bool valid(int i, int j) { return i >= 0 && j >= 0 && i < n && j < m; }

int main() {
	int i, j, ei, ej;
	scanf("%d %d", &n, &m);
	scanf("%d %d", &ei, &ej);
	priority_queue<no> pq;
	pq.push(no(--ei, --ej, 0, 1));
	scanf("%d %d", &ei, &ej); ei--; ej--;
	for(i = 0; i < n; i++)
		for(j = 0; j < m; j++)
			scanf(" %c", &g[i][j]);
	pii sol(0, 0);
	while(!pq.empty()) {
		no x = pq.top(); pq.pop();
		if(x.i == ei && x.j == ej) { sol = x.d; break; }
		if(seen[x.i][x.j]) continue;
		seen[x.i][x.j] = 1;
		for(i = 0; i < 8; i++) {
			int ni = x.i + dx[i], nj = x.j + dy[i];
			if(!valid(ni, nj) || seen[ni][nj] || g[ni][nj] == '0') continue;
			pq.push(no(ni, nj, x.d.fst + (g[x.i][x.j] != g[ni][nj]), x.d.snd + 1));
		}
	}
	printf("%d %d\n", sol.snd, sol.fst);
}
