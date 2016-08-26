#include <bits/stdc++.h>
using namespace std;
#define fst first
#define snd second
typedef unsigned long long ull;
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
template<typename T> inline T abs(T t) { return t < 0? -t : t; }
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }
const int MAX = (1 << 21) + 12, N = 25;
int n;
int memo[MAX];
int adj[N];
int grow(int bm) {
	int &b = memo[bm];
	if(b != -1) return b;
	b = 0;
	for(int i = 0; i < n; i++)
		if(bm & adj[i])
			b |= (1 << i);
	return b;
}

int pai[MAX];
char vert[MAX];
int dist[MAX];
bool solve() {
	queue<int> q;
	q.push((1 << n) - 1);
	memset(dist, -1, sizeof dist);
	dist[(1 << n) - 1] = 0;
	vert[(1 << n) - 1] = -1;
	while(!q.empty()) {
		int x = q.front(); q.pop();
		if(x == 0) return true;
		//printf("from\n%s\n", bitset<4>(x).to_string().c_str());
		for(int i = 0; i < n; i++) {
			int st = grow(x & (~(1 << i)));
			//printf("shoot %d to\n%s\n", i, bitset<4>(st).to_string().c_str());
			if(dist[st] != -1) continue;
			dist[st] = dist[x] + 1;
			pai[st] = x;
			vert[st] = i;
			q.push(st);
		}
	}
	return false;
}

int sn;
int main() {
	int m, i, a, b;
	while(true) {
		scanf("%d %d", &n, &m);
		if(!n) return 0;
		memset(adj, 0, sizeof adj);
		memset(memo, -1, sizeof memo);
		for(i = 0; i < m; i++) {
			scanf("%d %d", &a, &b);
			//a = rand() % n; b = rand() % n;
			adj[a] |= (1 << b);
			adj[b] |= (1 << a);
		}
		if(!solve()) { puts("Impossible"); continue; }
		sn = 0;
		int s = 0, *st = memo;
		while(s != ((1 << n) - 1)) {
			st[sn++] = vert[s];
			s = pai[s];
		}
		printf("%d:", sn);
		while(sn)
			printf(" %d", st[--sn]);
		putchar('\n');
	}
}
