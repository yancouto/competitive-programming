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
const int N = 11234;
int x[N], y[N];

ll cross(int a, int b, int c) {
	ll x1 = x[b] - x[a], y1 = y[b] - y[a];
	ll x2 = x[c] - x[a], y2 = y[c] - y[a];
	return x1 * y2 - x2 * y1;
}


int main() {
	int i, n, p;
	scanf("%d %d", &n, &p);
	for(i = 0; i < n; i++)
		scanf("%d %d", &x[i], &y[i]);
	int mx = 1;
	while(clock() < 0.85 * CLOCKS_PER_SEC) {
		int a = rand() % n, b = rand() % n;
		if(a == b) continue;
		int cur = 0;
		for(i = 0; i < n; i++)
			if(cross(a, b, i) == 0)
				cur++;
		mx = max(mx, cur);
	}
	if(100 * mx >= n * p) puts("YES");
	else puts("NO");
}
