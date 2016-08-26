#include <bits/stdc++.h>
using namespace std;
#define i first
#define j second
typedef unsigned long long ull;
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
template<typename T> inline T abs(T t) { return t < 0? -t : t; }
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }

int di[8] = {1, 1, -1, -1, 2, 2, -2, -2};
int dj[8] = {2, -2, 2, -2, 1, -1, 1, -1};

int dist[10][10];
inline int valid(int i, int j) { return i >= 0 && j >= 0 && i < 8 && j < 8; }
void go(pii p) {
	queue<pii> q;
	q.push(p);
	memset(dist, -1, sizeof dist);
	dist[p.i][p.j] = 0;
	while(!q.empty()) {
		pii x = q.front(); q.pop();
		for(int d = 0; d < 8; d++) {
			int ni = x.i + di[d], nj = x.j + dj[d];
			if(!valid(ni, nj) || dist[ni][nj] != -1) continue;
			q.push(pii(ni, nj));
			dist[ni][nj] = dist[x.i][x.j] + 1;
		}
	}
}

int main() {
	char a1, a2; int b1, b2;
	for_tests(tn, tt) {
		scanf(" %c %d %c %d", &a1, &b1, &a2, &b2);
		go(pii(a1 - 'a', b1 - 1));
		printf("%d\n", dist[a2 - 'a'][b2 - 1]);
	}
}
