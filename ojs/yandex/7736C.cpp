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

int h[1123];

int main() {
	int n, m, d1, c1, d2, c2;
	scanf("%d %d %d %d %d %d", &n, &m, &d1, &c1, &d2, &c2);
	for(int i = 0; i < n; i++) scanf("%d", &h[i]);
	sort(h, h + n);
	int mx = 0;
	for(int s2 = 0; s2 * c2 <= m; s2++) {
		int cm = m - s2 * c2;
		int i;
		for(i = 0; i < n; i++) {
			int ch = h[i] - s2 * d2;
			if(ch <= 0) continue;
			int s1 = (ch + d1 - 1) / d1;
			cm -= s1 * c1;
			if(cm < 0) break;
		}
		mx = max(mx, i);
	}
	printf("%d\n", mx);
}
