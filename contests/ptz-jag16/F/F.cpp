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

const int N = 112345;
int d[3][N];
int mn[3][N], mnc[3];
int c[N], n;
vector<int> adj[N], A[3];

int rep(int i) {
	if(c[i]) return mnc[c[i] - 1];
	else return i;
}

void bfs(int x) {
	queue<int> q;
	for(int i = 0; i < n; i++) {
		d[x][i] = INT_MAX;
		if(c[i]) mn[x][i] = mnc[c[i] - 1];
		else mn[x][i] = i;
	}
	for(int i : A[x])
		d[x][i] = 0, q.push(i);
	while(!q.empty()) {
		int g = q.front(); q.pop();
		for(int y : adj[g])
			if(d[x][y] == INT_MAX) {
				d[x][y] = d[x][g] + 1;
				if(c[y]) {
					for(int z : A[c[y] - 1]) {
						d[x][z] = d[x][g] + 1;
						q.push(z);
					}
				} else q.push(y);
				mn[x][rep(y)] = min(mn[x][rep(y)], mn[x][g]);
			} else if(d[x][y] == d[x][g] + 1)
				mn[x][rep(y)] = min(mn[x][rep(y)], mn[x][g]);
	}
}

int calc(int i) { return d[0][i] + d[1][i] + d[2][i]; }

int main() {
	int a[3], x, y, i, j;
	scanf("%d %d %d %d", &n, &a[0], &a[1], &a[2]);
	for(j = 0; j < 3; j++) {
		mnc[j] = INT_MAX;
		for(i = 0; i < a[j]; i++) {
			scanf("%d", &x); x--;
			A[j].pb(x);
			c[x] = j + 1;
			mnc[j] = min(mnc[j], x);
		}
	}
	for_tests(mm, mi) {
		scanf("%d %d", &x, &y); x--; y--;
		adj[x].pb(y);
		adj[y].pb(x);
	}
	bfs(0);
	bfs(1);
	bfs(2);
	int ans = INT_MAX;
	for(i = 0; i < n; i++)
		if(calc(i) < ans)
			ans = calc(i);
	int ai = INT_MAX;
	for(i = 0; i < n; i++)
		if(calc(i) == ans)
			ai = min(ai, min(min(mn[0][i], mn[1][i]), mn[2][i]));
	printf("%d %d\n", ans, ai + 1);
}
