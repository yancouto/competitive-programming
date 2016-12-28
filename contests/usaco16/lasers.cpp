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
queue<int> q;
int dist[N];
void add(vector<int> &v, int d) {
	for(int i : v)
		if(dist[i] == -1) {
			dist[i] = d;
			q.push(i);
		}
	v.clear();
}

int x[N], y[N];

map<int, vector<int>> xs, ys;

int main() {
	freopen("lasers.in", "r", stdin);
	freopen("lasers.out", "w", stdout);
	int i, n, xl, yl;
	memset(dist, -1, sizeof dist);
	scanf("%d %d %d %d %d", &n, &xl, &yl, &x[0], &y[0]); n++;
	for(i = 1; i < n; i++)
		scanf("%d %d", &x[i], &y[i]);
	for(i = 0; i < n; i++) {
		xs[x[i]].pb(i);
		ys[y[i]].pb(i);
	}
	add(xs[xl], 0); add(ys[yl], 0);
	while(!q.empty()) {
		i = q.front(); q.pop();
		add(xs[x[i]], dist[i] + 1);
		add(ys[y[i]], dist[i] + 1);
	}
	printf("%d\n", dist[0]);
}
