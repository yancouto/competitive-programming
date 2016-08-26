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

int dist[2000], a[6];
int main() {
	int i;
	for_tests(t, tt) {
		memset(dist, -1, sizeof dist);
		for(i = 0; i < 6; i++)
			scanf("%d", &a[i]);
		dist[0 + 500] = 0;
		queue<int> q;
		q.push(0);
		while(!q.empty()) {
			int x = q.front(); q.pop();
			if(x < -100 || x > 200) continue;
			for(i = 0; i < 6; i++) {
				if(dist[x - a[i] + 500] == -1) {
					dist[x - a[i] + 500] = dist[x + 500] + 1;
					q.push(x - a[i]);
				}
				if(dist[x + a[i] + 500] == -1) {
					dist[x + a[i] + 500] = dist[x + 500] + 1;
					q.push(x + a[i]);
				}
			}
		}
		int mx = 0, tot = 0;
		for(i = 1; i <= 100; i++) {
			tot += dist[i + 500];
			mx = max(mx, dist[i + 500]);
		}
		printf("%d.%02d %d\n", tot / 100, tot % 100, mx);
	}
}
