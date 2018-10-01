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

int d[3612];
int a[11];

int main() {
	for_tests(tn, tt) {
		int i, n, t;
		scanf("%d %d", &n, &t);
		for(i = 0; i < n; i++) scanf("%d", &a[i]);
		memset(d, -1, sizeof d);
		queue<int> q;
		q.push(0); d[0] = 0;
		while(!q.empty()) {
			int x = q.front(); q.pop();
			if(x == t) break;
			for(i = 0; i < n; i++) {
				int y = max(0, min(x + a[i], 3600));
				if(d[y] == -1) {
					d[y] = d[x] + 1;
					q.push(y);
				}
			}
		}
		for(i = 0; ; i++) {
			if(d[t + i] != -1) {
				printf("%d %d\n", d[t + i], i);
				break;
			}
		}
	}
}
