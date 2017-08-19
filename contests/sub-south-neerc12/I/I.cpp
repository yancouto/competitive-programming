#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> pii;
#define pb push_back

const int N = 112345;
vector<int> adj[N];
int d[N];

int dist(int a, int b) {
	queue<int> q;
	memset(d, -1, sizeof d);
	d[a] = 0;
	q.push(a);
	while(!q.empty()) {
		int x = q.front(); q.pop();
		for(int y : adj[x]) {
			if(d[y] == -1) {
				d[y] = d[x] + 1;
				q.push(y);
			}
		}
	}
	return d[b];
}

int main() {
#ifdef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	int a, b, n, m, i;
	scanf("%d %d", &n, &m);
	for(i = 0; i < m; i++) {
		scanf("%d %d", &a, &b); a--; b--;
		adj[a].pb(b);
		adj[b].pb(a);
	}
	for(a = 0; a <= 2; a++) {
		int win = 0;
		for(b = 0; b <= 2; b++) {
			if(a == b) continue;
			printf("(%d,%d): %d, %d\n", a+1, b+1, dist(a, 3 - a - b), dist(b, 3 - a - b));
			if(dist(a, 3 - a - b) <= dist(b, 3 - a - b)) {
				printf("(%d, %d) win\n", a+1, b+1);
				win++;
			}
		}
		if(win == 2) {
			puts("1");
			return 0;
		}
	}
	puts("2");
}
