#include <bits/stdc++.h>
using namespace std;
#define x first
#define y second
typedef unsigned long long ull;
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)
template<typename T> inline T abs(T t) { return t < 0? -t : t; }
const ll modn = 1000000007;
inline ll mod(ll x) { return x % modn; }

int x[8] = {1, -1, 1, -1, 2, -2, 2, -2};
int y[8] = {2, -2, -2, 2, 1, -1, -1, 1};

int best[70][70];

void pre() {
	memset(best, -1, sizeof best);
	queue<pii> q;
	q.push(pii(0, 0)); best[0 + 32][0 + 32] = 0;
	while(!q.empty()) {
		pii p = q.front(); q.pop();
		for(int k = 0; k < 8; k++) {
			int nx = p.x + x[k], ny = p.y + y[k];
			if(abs(nx) > 30 || abs(ny) > 30 || best[nx + 32][ny + 32] != -1) continue;
			best[nx + 32][ny + 32] = best[p.x + 32][p.y + 32] + 1;
			q.push(pii(nx, ny));
		}
	}
}

ll solve(int a, int b, ll X, ll Y) {
	int d = y[b] * x[a] - y[a] * x[b];
	if(!d || (abs(Y * x[a] - ll(y[a]) * X) % d)) return LLONG_MAX;
	ll B = (Y * x[a] - ll(y[a]) * X) / d;
	if(abs(X - B * x[b]) % x[a]) return LLONG_MAX;
	ll A = ((X - B * x[b]) / x[a]);
	if(A < 0 || B < 0) return LLONG_MAX;
	//printf("A*%d + B*%d = %lld\nA*%d + B*%d = %lld\n", x[a], x[b], X, y[a], y[b], Y);
	//printf("solution A=%lld and B=%lld\n", A, B);
	return B + ((X - B * x[b]) / x[a]);
}

ll dist(int x1, int y1, int x2, int y2) {
	ll mn = 1500000000000000000;
	for(int k1 = 0; k1 < 8; k1++)
		for(int k2 = k1 + 1; k2 < 8; k2++)
			mn = min(mn, solve(k1, k2, x2 - x1, y2 - y1));
	return mn;
}

int main() {
	int i, j, X, Y;
	pre();
	while(scanf("%d %d", &X, &Y)) {
		ll mn = LLONG_MAX;
		for(i = -20; i <= 20; i++)
			for(j = -20; j <= 20; j++) {
				//printf("[%d, %d] %lld = %d + %lld\n", i, j, mn, best[i + 32][j + 32], dist(i, j, X, Y));
				mn = min(mn, ll(best[i + 32][j + 32]) + dist(i, j, X, Y));
			}
		printf("%lld\n", mn);
	}
}
