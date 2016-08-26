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
char s[26];
int dist[1 << 13][1 << 13];

struct no { int x, y; };

void solve(int a, int b) {
	deque<no> q;
	q.pb({a, b});
	dist[a][b] = 1;
	int d = -1;
	while(!q.empty()) {
		no x = q.front(); q.pop_front();
		a = x.x; b = x.y;
		int dd = dist[a][b];
		int a2 = (a & (~7)) | (b >> 10),
			b2 = (b & (~(7 << 10))) | ((a & 7) << 10);
		if(!dist[a2][b2] || dist[a2][b2] > dd + 1) q.pb({a2, b2}), dist[a2][b2] = dd + 1;
		b2 = (b >> 1) | ((b & 1) << 12);
		a2 = (a >> 1) | ((a & 1) << 12);
		if(!dist[a2][b] || dist[a2][b] > dd) q.push_front({a2, b}), dist[a2][b] = dd;
		if(!dist[a][b2] || dist[a][b2] > dd) q.push_front({a, b2}), dist[a][b2] = dd;
	}
}

int main() {
	solve(0, (1 << 13) - 1);
	while(scanf("%s", s) != EOF) {
		int a = 0, b = 0;
		for(int i = 0; i < 13; i++)
			a |= ((s[i] == 'y') << (12 - i));
		for(int i = 13; i < 26; i++)
			b |= ((s[i] == 'y') << (25 - i));
		printf("%d\n", dist[a][b] - 1);
	}
}
