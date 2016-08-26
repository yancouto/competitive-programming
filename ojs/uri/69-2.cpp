#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef pair<int, int> pii;
typedef unsigned long long ull;
typedef long long ll;
typedef long double ld;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
template<typename T> inline T abs(T t) { return t < 0? -t : t; }

const int inf = 100000000;
int d;
int dist[100009], bad[100009];
void tr(queue<int> &q, int x, int y) {
	if(y <= 0 || y > 100000 || bad[y]) return;
	if(dist[y] != -1) return;
	dist[y] = dist[x] + 1;
	q.push(y);
}

int solve(int o) {
	memset(dist, -1, sizeof dist);
	queue<int> q;
	q.push(o);
	dist[o] = 0;
	while(!q.empty()) {
		int x = q.front(); q.pop();
		if(x == d) return dist[x];
		tr(q, x, x + 1);
		tr(q, x, x - 1);
		tr(q, x, x * 2);
		tr(q, x, x * 3);
		if(!(x & 1)) tr(q, x, x / 2);
	}
	return -1;
}

int main() {
	int i, o, k, x;
	while(true) {
		scanf("%d %d %d", &o, &d, &k);
		if(!o) return 0;
		memset(bad, 0, sizeof bad);
		for(i = 0; i < k; i++) {
			scanf("%d", &x);
			bad[x] = true;
		}
		int k = solve(o);
		printf("%d\n", k);
	}
}
