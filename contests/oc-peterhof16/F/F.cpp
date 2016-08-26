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

const int N = 6000;
int dist[N][N];

int main() {
	int a, b;
	for(a = 0; a <= 50; a++)
		for(b = a + 1; b <= 50; b++) {
			if(((a + b) % 2) == 0 && b == 50) putchar('\n');
			if(((a + b) % 2) == 0) continue;
			//scanf("%d %d", &a, &b);
			int di[8] = {a, -a, a, -a, b, -b, b, -b};
			int dj[8] = {b, -b, -b, b, a, -a, -a, a};
			queue<pii> q;
			memset(dist, -1, sizeof dist);
			dist[N/2][N/2] = 0;
			q.push(pii(N/2, N/2));
			bool f = false;
			while(!q.empty()) {
				pii x = q.front(); q.pop();
				if(x.i == N/2 && x.j == (N/2)+1) {
					f = true;
					printf("f(%d, %d) = %2d\n", a, b, dist[x.i][x.j]);
					break;
				}
				for(int d = 0; d < 8; d++) {
					pii y(x.i + di[d], x.j + dj[d]);
					if(y.i < 0 || y.i >= N || y.j < 0 || y.j >= N) continue;
					if(dist[y.i][y.j] != -1) continue;
					dist[y.i][y.j] = dist[x.i][x.j] + 1;
					q.push(y);
				}
			}
		}
}
