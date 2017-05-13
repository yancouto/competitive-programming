#include <bits/stdc++.h>
using namespace std;
#define p first
#define b second
typedef long long ll;
typedef pair<int, int> pii;
#define pb push_back
#define for_tests(t, tt) int t; scanf("%d", &t); for(int tt = 1; tt <= t; tt++)

pii t[112345];

int main() {
	int i, n, c, m;
	for_tests(tn, tt) {
		scanf("%d %d %d", &n, &c, &m);
		int pA = 0, pB = 0, sA = 0, sB = 0;
		for(i = 0; i < m; i++) {
			scanf("%d %d", &t[i].p, &t[i].b);
			if(t[i].p == 1 && t[i].b == 1) pA++;
			else if(t[i].p >= 2 && t[i].b == 1) sA++;
			else if(t[i].p == 1) pB++;
			else sB++;
		}
		printf("A: %d %d\nB: %d %d\n", pA, sA, pB, sB);
		int ans = pA + pB;
		sA -= min(sA, pB);
		sB -= min(sB, pA);
		ans += max(sA, sB);
		printf("Case #%d: ", tt);
		printf("%d %d\n", ans, min(sA, sB));
	}
}
